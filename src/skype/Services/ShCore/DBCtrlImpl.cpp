#include "DBCtrlImp.h"
#include "DBEventImpl.h"
#include "PlatformUtilsImpl.h"
#include "skype_helpers.h"

#include <atomic>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <future>
#include <sstream>

#include "core/error_codes.h"
#include "core/ref_obj_qi_ptr.h"
#include "common/mutex.h"
#include "common/filewatcher.h"
#include "common/string.h"
#include "common/enum.h"
#include "common/string_helper.h"
#include "common/time_calculator.h"
#include "core/exceptions.h"

#include "litesql.hpp"
#include "skype_main_db.hpp"
#include "history_main_db.hpp"

BOSS_DECLARE_RUNTIME_EXCEPTION(DBCtrl)

using Boss::ref_ptr;
using Boss::qi_ptr;
using Boss::IString;
using Boss::String;
using Boss::StringHelper;
using Boss::Base;

using std::atomic; using std::atomic_int; using std::cout; using std::endl;
using namespace litesql;

namespace skype_sc {

class DBControllerImplPrivate {
	friend class DBControllerImpl;
public:

	DBControllerImplPrivate(DBControllerImpl *p_q)
		: q(p_q)
		, m_watching_bound_line(-1)
		, m_pu(Base<PlatformUtilsImpl>::Create()) {
		try {

		} catch (const std::exception &e) {
			cout << "Error in constructor DBControllerImplPrivate" << endl;
			throw std::runtime_error(e.what());
		}
	}
	~DBControllerImplPrivate() {
		cout << "~Controller impl private" << endl;
		m_w.reset(0);
	}

	template<typename T = void>
	void start() {
		if (isRunning()) return;
		if (m_filename.empty()) {
			std::cout << "Filename is empty, nothing to start" << std::endl;
			return;
		}
		try {
			std::string history_db_file = m_historyDBDir.empty() ? "history.db" : m_historyDBDir + "/history.db";
			history_db.reset(new HistoryDB::history("sqlite3", std::string("database=") + history_db_file));
			history_db->verbose = false;
			if (history_db->needsUpgrade()) {
				history_db->upgrade();
			}
			skype_main.reset(new SkypeDB::main("sqlite3", std::string("database=") + m_filename));
			skype_main->verbose = false;
			auto accs = select<SkypeDB::Accounts>(*skype_main).all();
			assert(accs.size() == 1);
			auto usr = convert<SkypeDB::Accounts, HistoryDB::Users> (accs.at(0));
			me = usr.name;
			cache_element(usr);

			cacheHistoryDB();
			import();
			m_watching_bound_line = check_bound();
			if (!m_w.get()) {
				m_w.reset(new sm::filewatcher(m_filename, [this](std::string file, int mode) {
					using namespace SkypeDB;
					std::lock_guard<Boss::Mutex> lock(m_mutex);
					uint newBound = check_bound();
					//cout << (mode == sm::filewatcher::e_modify ? "modify" : "access") << endl;
					if (newBound != m_watching_bound_line) {
						int oldBound = m_watching_bound_line;
						auto ms = select<SkypeDB::Messages>(*skype_main,
								(Messages::Id > oldBound) && (Messages::Id <= newBound)).
										orderBy(Messages::Timestamp, true).all();
						std::for_each(ms.begin(), ms.end(), [this](const Messages &source) {
							cout << source.id << " - " << source.body_xml << std::endl;
							HistoryDB::Messages hm = convert<SkypeDB::Messages, HistoryDB::Messages>(source);
							cache_element(hm);
							for (auto obs : m_observers) {
								auto db_event = Base<DBEventImpl>::Create();
								db_event->SetMessage(convert<HistoryDB::Messages, ref_ptr<IMessage>>(hm).Get());
								//std::async(std::launch::async, &IDBObserver::ReactOnDbChanged, obs, db_event.Get()); call async if needed
								obs->ReactOnDbChanged(db_event.Get());
							}
						});
						m_watching_bound_line = newBound;
					}
				}));
			}
			m_w->start();
		} catch (const std::exception &e) {
			throw runtime_error(e.what());
		}
	}
	void stop() {
		if (!isRunning()) return;
		m_w->stop();
	}
	void addObserver(IDBObserver *obsr) {
		auto iter = std::find(m_observers.begin(), m_observers.end(), obsr);
		if (iter != m_observers.end()) {
			std::cout << "Observer " << obsr << " allready exists" << std::endl;
			return;
		}
		m_observers.push_back(obsr);
	}
	void removeObserver(IDBObserver *obsr) {
		auto iter = std::find(m_observers.begin(), m_observers.end(), obsr);
		if (iter == m_observers.end()) {
			std::cout << "Observer " <<  obsr << " is not registered" << std::endl;
			return;
		}
		m_observers.erase(iter);
	}
	void setWatchFile(std::string &&str) {
		if (isRunning()) {
			restart(str, m_historyDBDir);
			return;
		}
		if (str == m_filename) {
			return;
		}
		m_filename = str;
	}
	uint check_bound() {
		SelectQuery q;
		q.result("max(id)");
		q.source(SkypeDB::Messages::table__);
		std::lock_guard<Boss::Mutex> lock(m_mutex);
		int result = m_watching_bound_line;
		try {
			result =  atoi(skype_main->query(q)[0][0]);
		} catch (const litesql::CorruptError &e) {
			cout << "Error: " << e << endl;
		}
		return result;
	}

	template<typename T = void>
	void import() {
		auto start_time = Boss::GetTimeMs64();
		std::unordered_map<std::string, std::string> chats_hash, contacts_hash;
		auto contacts_cursor = select<SkypeDB::Contacts>(*skype_main).cursor();
		cout << "Create users base" << endl;
		history_db->begin();
		for (;contacts_cursor.rowsLeft();contacts_cursor++) {
			SkypeDB::Contacts ctc = *contacts_cursor;
			contacts_hash.emplace(ctc.skypename, ctc.fullname);
			HistoryDB::Users hu = convert<SkypeDB::Contacts, HistoryDB::Users>(ctc);
			cache_element<HistoryDB::Users>(hu);
		}
		history_db->commit();

		SelectQuery q;
		q.result("count(*)");
		q.source(SkypeDB::Messages::table__);
		auto cnt = atoi(skype_main->query(q)[0][0]);

		int counter = 0, transac_cnt = 0, package = 2000, percent = 0, cut = 0;
		cout << "Importing skype messages" << endl;
		auto messages_vec = select<SkypeDB::Messages>(*skype_main).orderBy(SkypeDB::Messages::Timestamp).all();
		history_db->begin();
		auto messages_cache = std::get<DBCache<HistoryDB::Messages>>(m_hash);
		for (auto sky_mes : messages_vec) {
			percent = counter * 100 / (cnt - 1);
			if (!messages_cache.contains(sky_mes.id)) {
				if (!(transac_cnt % package)) {
					history_db->begin();
					cout << "\rHistorydb begin" << endl;
				}
				cout << "\r" << percent << "% - "<< counter << " Not in cache, Converting" << endl;
				for (;;) {
					try {
						HistoryDB::Messages hm = convert<SkypeDB::Messages, HistoryDB::Messages>(sky_mes);
						break;
					} catch (const std::exception &e) {
						cout << "\r" << e.what();
					}
				}
				if ((transac_cnt % package) == package - 1 || counter == cnt - 1) {
					history_db->commit();
					cout << "\rHistorydb commit" << endl;
				}
				transac_cnt++;
			}

			cout << "\r" << counter << " - " << percent << "%" << flush;
      		counter++;
			if (!--cut) break;
		}
		history_db->commit();
		cout << endl << "Succeeded! Time: " << human_readable(GetTimeMs64() - start_time) << endl;
	}

	template<typename T = void>
	void recent(IEnum **result) { //2 weeks
		using namespace HistoryDB;
		ref_ptr<Enum> res = Base<Enum>::Create();
		auto messages = select<Messages>(*history_db, Messages::Skype_timestamp > (time(nullptr) - (2 * 7 * 24 * 60 * 60)))
				.orderBy(Messages::Skype_timestamp, false).all();
		for (Messages m : messages) {
			ref_ptr<IMessage> im(convert<Messages, ref_ptr<IMessage>>(m));
			res->AddItem(im);
		}

        res.QueryInterface(result);
	}

	template<typename T = void>
	void getMessages(IMessageCallback *callback) {
		std::lock_guard<Mutex> lock(m_mutex);

		using namespace HistoryDB;
		ref_ptr<Enum> res = Base<Enum>::Create();
		cout << "Dump all messages..." << endl;
		UInt ct = GetTimeMs64();
		auto messages = select<Messages>(*history_db).orderBy(Messages::Skype_timestamp, false).all();
		cout << "Done; elapsed: " << GetTimeMs64() - ct << endl;
		for (Messages m : messages) {
			ref_ptr<IMessage> im(convert<Messages, ref_ptr<IMessage>>(m));
			callback->Process(im.Get());
		}
	}

	template<typename T = void>
	void getMessagesAsync(IMessageCallback *callback) {
		std::async(std::launch::async, &DBControllerImplPrivate::getMessages, this, callback);
	}

	template<typename T = void>
	void restart(const std::string &new_filename, const std::string &history_db_path) {
		stop();
		m_w.reset(nullptr);
		m_watching_bound_line = -1;
		if (new_filename != m_filename) {
			skype_main.reset(nullptr);
			m_filename = new_filename;
		}
		if (history_db_path != m_historyDBDir) {
			history_db.reset(nullptr);
			m_historyDBDir = m_pu.Exists(history_db_path) ? history_db_path : "";
		}
		clearCache();
		start();
	}

	template<typename T = void>
	void setHistoryDBPath(const std::string &hdbpath) {
		if (!m_pu.IsDir(hdbpath)) {
			throw DBCtrlException("Path: " + hdbpath + " is not a directory");
		}
		if (hdbpath != m_historyDBDir) {
			clearCache();
		}
		m_historyDBDir = hdbpath;
	}

	std::string conv_body(const std::string &resource) {
		std::string converted(resource);
		return std::move(converted);
	}

	template<typename Dest, typename Source>
	Dest getOrCreate(const std::string &key, const litesql::Expr &condition) {
		auto hash = std::get<DBCache<Dest>>(m_hash);
		if (hash.count(key)) {
			return hash.at(key);
		}
		auto element = select<Source>(*skype_main, condition).all().at(0);
		auto converted = convert<Source, Dest>(element);
		converted.update();
		cache_element<Dest>(std::move(converted));

		return converted;
	}

	bool isRunning() const {
		return m_w.get();
	}

	template<typename T>
	class DBCache {
	public:
		typedef typename T::cache_key_type key_type;
		inline bool contains(const key_type &key) const {
			return map.count(key);
		}
		void insert(const key_type &key, const T &val) {
			map.emplace(key, val);
		}
		T at(const key_type &key) const {
			return map.at(key);
		}
		void sort() {
		}
		void free() {
			map.clear();
		}
	private:
		std::unordered_map<key_type, T> map;

	};

	void cacheHistoryDB() {
		Boss::uint64 start;
		cout << "Caching users..." << endl;
		start = Boss::GetTimeMs64();
		cache_m<HistoryDB::Users>();
		cout << "Caching users time: " << Boss::GetTimeMs64() - start << endl;
		cout << "Caching messages..." << endl;
		start = Boss::GetTimeMs64();
	    cache_m<HistoryDB::Messages>();
	    cout << "Caching messages time: " << Boss::GetTimeMs64() - start << endl;
	    cout << "Finished Caching" << endl;
	}
	void clearCache() {
		std::get<DBCache<HistoryDB::Users>>(m_hash).free();
		std::get<DBCache<HistoryDB::Messages>>(m_hash).free();
		std::get<DBCache<SkypeDB::Contacts>>(m_hash).free();
	}

	template<typename T, typename F>
	void cache_func(F func) {
		auto rows = select<T>(*history_db).all();
		std::for_each(rows.begin(), rows.end(), func);
	}

	template<typename T>
	void cache_m() {
		auto rows = select<T>(*history_db).all();
		std::for_each(rows.begin(), rows.end(), [this] (T &row) {
			auto method = row.cache_field();
			std::get<DBCache<T>>(m_hash).insert(row.*method, std::move(row));
		});
		std::get<DBCache<T>>(m_hash).sort();
	}

	template<typename T>
	void cache_element(T &element) {
		auto method = element.cache_field();
		std::get<DBCache<T>>(m_hash).insert(element.*method, element);
	}
	template<typename From, typename To>
	To convert(const From &);

private:
	DBControllerImpl *q;
	std::string m_filename;
	std::string m_historyDBDir;
	std::unique_ptr<sm::filewatcher> m_w = nullptr;
	atomic_int m_watching_bound_line;
	Boss::Mutex m_mutex;
	std::unique_ptr<SkypeDB::main> skype_main;
	std::unique_ptr<HistoryDB::history> history_db;
    std::tuple< DBCache<HistoryDB::Users>,
				DBCache<HistoryDB::Messages>,
				DBCache<SkypeDB::Contacts>
		      > m_hash;
	std::string me;
	std::vector<IDBObserver*> m_observers;
	PlatformUtils_hlpr m_pu;
}; //class DBControllerImplPrivate

template<>
HistoryDB::Users DBControllerImplPrivate::convert(const SkypeDB::Accounts &source) {
	HistoryDB::Users dest(*history_db);
	dest.name        = static_cast<std::string>(source.skypename);
	dest.displayname = static_cast<std::string>(source.fullname);
	dest.update();

	return std::move(dest);
}
template<>
HistoryDB::Users DBControllerImplPrivate::convert(const SkypeDB::Contacts &source) {
	HistoryDB::Users dest(*history_db);
	dest.name            = static_cast<std::string>(source.skypename);
	dest.displayname     = static_cast<std::string>(source.fullname);
	dest.lastmessagetime = static_cast<int>(source.lastused_timestamp);
	dest.update();

	return std::move(dest);
}

template<>
HistoryDB::Conversations DBControllerImplPrivate::convert(const SkypeDB::Conversations &source) {
	HistoryDB::Conversations dest(*history_db);
	dest.friendlyname = static_cast<std::string>(source.displayname);
	dest.skypeid = static_cast<int>(source.id);
	dest.update();
	auto skype_participants = select<SkypeDB::Participants>(*skype_main, SkypeDB::Participants::Convo_id == source.id).all();
	auto usr_cache = std::get<DBCache<HistoryDB::Users>>(m_hash);
	for (SkypeDB::Participants sk_part : skype_participants) {
		if (sk_part.identity == me) {
			assert(usr_cache.contains(me));
			if (usr_cache.contains(me)) {
				auto usr_me = usr_cache.at(me);
				dest.users().link(usr_me);
			}
		} else {
			auto contact_vec = select<SkypeDB::Contacts>(*skype_main, SkypeDB::Contacts::Skypename == sk_part.identity).all();
			if (contact_vec.size() == 1) {//User is in contact list
				SkypeDB::Contacts contact = contact_vec.at(0);
				if (usr_cache.contains(contact.skypename)) {
					dest.users().link(usr_cache.at(contact.skypename));
				} else {
					HistoryDB::Users nuser = convert<SkypeDB::Contacts, HistoryDB::Users>(contact);
					dest.users().link(nuser);
					cache_element<HistoryDB::Users>(nuser);
				}
			}
		}
	}
	return std::move(dest);
}

template<>
HistoryDB::Messages DBControllerImplPrivate::convert(const SkypeDB::Messages &source) {
	HistoryDB::Messages dest(*history_db);
	dest.skype_id = (int)source.id;
	dest.timestamp = (int)time(nullptr);
	dest.skype_timestamp = (int)source.timestamp;
	dest.body = conv_body(source.body_xml);
	dest.author = static_cast<std::string>(source.author);
	auto skype_conv   = select<SkypeDB::Conversations>(*skype_main, SkypeDB::Conversations::Id == source.convo_id).all().at(0);
	dest.update();
	auto history_conv = convert<SkypeDB::Conversations, HistoryDB::Conversations>(skype_conv);
	dest.conversation().link(history_conv);

	return std::move(dest);
}

template<>
HistoryDB::Chats DBControllerImplPrivate::convert(const SkypeDB::Chats &source) {
	HistoryDB::Chats dest(*history_db);
	dest.name         = static_cast<std::string>(source.name);
	dest.owner        = static_cast<std::string>(source.friendlyname);
	dest.creationtime = static_cast<int>(source.timestamp);

	return std::move(dest);
}

template<>
ref_ptr<IUser> DBControllerImplPrivate::convert(const HistoryDB::Users &source) {
	using namespace HistoryDB;
	Users src_cpy = source;
	ref_ptr<IUser> dest = Base<DBUser>::Create();
	std::string display_name = static_cast<std::string>(source.displayname) == "NULL" ? source.name : source.displayname;
	dest->SetName(Base<String>::Create(display_name).Get());
	dest->SetSkypeName(Base<String>::Create(source.name).Get());

	return dest;
}

template<>
ref_ptr<IConversation> DBControllerImplPrivate::convert(const HistoryDB::Conversations &source) {
	using namespace HistoryDB;
	auto dest = Base<DBConversation>::Create();
	dest->SetName(Base<String>::Create(source.friendlyname).Get());
	dest->SetId(source.id);
	dest->SetSkypeId(source.skypeid);
	auto source_users = const_cast<Conversations&>(source).users().get().all(); //Shouldn't create unnecessary copy
	ref_ptr<Enum> dest_users = Base<Enum>::Create();
	for (auto usr : source_users) {
		ref_ptr<IUser> iuser = convert<Users, ref_ptr<IUser>>(usr);
		dest_users->AddItem(iuser);
	}
	dest->SetUsers(dest_users.Get());

	return dest;
}

template<>
ref_ptr<IMessage> DBControllerImplPrivate::convert(const HistoryDB::Messages &source) {
	using namespace HistoryDB;
	ref_ptr<IMessage> dest = Base<DBMessage>::Create();
	dest->SetBody(Base<String>::Create(source.body).Get());
	dest->SetId(source.id);
	dest->SetSkypeId(source.skype_id);
	dest->SetAuthor(Base<String>::Create(source.author).Get());
	dest->SetTimestamp(source.timestamp);
	dest->SetSkypeTimestamp(source.skype_timestamp);
	auto history_conv = const_cast<Messages&>(source).conversation().get().one(); //Shouldn't create unnecessary copy
	auto dest_conversation = convert<Conversations, ref_ptr<IConversation>>(history_conv);
	dest->SetConversation(dest_conversation.Get());

	return dest;
}

DBControllerImpl::DBControllerImpl()
	: d(new DBControllerImplPrivate(this)) {

}

DBControllerImpl::~DBControllerImpl() {
	cout << "~DBControllerImpl()" << endl;
}

Boss::RetCode BOSS_CALL DBControllerImpl::Import() {
	cout << "DBControllerImpl::Import()" << endl;
	d->import();
	return Boss::Status::Ok;
}

Boss::RetCode BOSS_CALL DBControllerImpl::Recent(Boss::IEnum **result) {
	cout << "DBControllerImpl::Recent()" << endl;
	d->recent(result);
	return Boss::Status::Ok;
}

Boss::RetCode BOSS_CALL DBControllerImpl::GetMessagesAsync(IMessageCallback *callback) {
	cout << "DBControllerImpl::GetMessagesAsync()" << endl;
	d->getMessagesAsync(callback);
	return Boss::Status::Ok;
}


Boss::RetCode BOSS_CALL DBControllerImpl::Restart(Boss::IString *skype, Boss::IString *history) {
	std::cout << "DBWatcherImpl::Reset()" << std::endl;
	d->restart(StringHelper(skype).GetString<>(), StringHelper(history).GetString<>());
	return Boss::Status::Ok;
}

Boss::RetCode BOSS_CALL DBControllerImpl::SetDBPath(Boss::IString *ptr) {
	std::cout << "DBWatcherImpl::SetDBPath()" << std::endl;
	d->setHistoryDBPath(StringHelper(ptr).GetString<>());
	return Boss::Status::Ok;
}

Boss::RetCode BOSS_CALL DBControllerImpl::SetWatchFile(Boss::IString *p_str) {
	d->setWatchFile(StringHelper(p_str).GetString<IString::AnsiString>());
	return Boss::Status::Ok;
}
Boss::RetCode BOSS_CALL DBControllerImpl::GetWatchFile(Boss::IString **pptr) {
	ref_ptr<IString> str = Base<String>::Create(d->m_filename);
	return str.QueryInterface(pptr);
}

Boss::RetCode BOSS_CALL DBControllerImpl::Start() {
	std::cout << "DBWatcherImpl::Start()" << std::endl;
	d->start();
	return Boss::Status::Ok;
}
Boss::RetCode BOSS_CALL DBControllerImpl::Stop() {
	std::cout << "DBWatcherImpl::Stop()" << std::endl;
	d->stop();
	return Boss::Status::Ok;
}

Boss::RetCode BOSS_CALL DBControllerImpl::AddObserver(IDBObserver *obsr) {
	std::cout << "DBWatcherImpl::AddObserver()" << std::endl;
	d->addObserver(obsr);
	return Boss::Status::Ok;
}
Boss::RetCode BOSS_CALL DBControllerImpl::RemoveObserver(IDBObserver *obsr) {
	std::cout << "DBWatcherImpl::RemoveObserver()" << std::endl;
	d->removeObserver(obsr);
	return Boss::Status::Ok;
}

} //namespace skype_sc
