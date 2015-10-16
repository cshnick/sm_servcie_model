#include "DBCtrlImp.h"

#include <atomic>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <functional>

#include "core/error_codes.h"
#include "core/ref_obj_qi_ptr.h"
#include "common/mutex.h"
#include "common/filewatcher.h"
#include "common/string.h"
#include "common/string_helper.h"
#include "core/exceptions.h"

#include "litesql.hpp"
#include "skype_main_db.hpp"
#include "history_main_db.hpp"

using Boss::RefObjPtr;
using Boss::RefObjQIPtr;
using Boss::IString;
using Boss::String;
using Boss::StringHelper;
using Boss::Base;

using std::atomic; using std::atomic_int; using std::cout; using std::endl;
using namespace litesql;

namespace skype_sc {

class DBControllerImplPrivate {
	friend class DBControllerImpl;
	DBControllerImplPrivate(DBControllerImpl *p_q)
		: q(p_q)
		, m_watching_bound_line(-1) {
		try {
			history_db.reset(new HistoryDB::history("sqlite3", std::string("database=") + "history.db"));
			if (history_db->needsUpgrade()) {
				history_db->upgrade();
			}
		} catch (const std::exception &e) {
			cout << "Error in constructor DBControllerImplPrivate" << endl;
			throw std::runtime_error(e.what());
		}
	}
	void start() {
		if (m_filename.empty()) {
			std::cout << "Filename is empty, nothing to start" << std::endl;
			return;
		}
		if (!skype_main.get()) {
			try {
				skype_main.reset(new SkypeDB::main("sqlite3", std::string("database=") + m_filename));
				skype_main->verbose = false;
			} catch (const std::exception &e) {
				throw runtime_error(e.what());
			}
		}
		cacheHistoryDB();
		import();
		m_watching_bound_line = check_bound();
		if (!m_w.get()) {
			m_w.reset(new sm::filewatcher(m_filename, [this](std::string file, int mode) {
				using namespace SkypeDB;
				//std :: cout << file << "; mode: "<< (mode == sm::filewatcher::e_modify ? "modify" : "access") << std::endl;
				std::lock_guard<Boss::Mutex> lock(m_mutex);
				uint newBound = check_bound();
				cout << (mode == sm::filewatcher::e_modify ? "modify" : "access") << endl;
				if (newBound != m_watching_bound_line) {
					int oldBound = m_watching_bound_line;
					auto ms = select<SkypeDB::Messages>
						(*skype_main, (Messages::Id > oldBound) && (Messages::Id <= newBound))
						     .orderBy(Messages::Id, false).all();
					std::for_each(ms.begin(), ms.end(), [this](const Messages &source) {
						cout << source.id << " - " << source.body_xml << std::endl;
						HistoryDB::Messages dest(*history_db);
						dest.skype_id = (int)source.id;
						dest.timestamp = (int)time(nullptr);
						dest.skype_timestamp = (int)source.timestamp;
						dest.body = conv_body(source.body_xml);
//						dest.chat_id =   static_cast<int>(getOrCreate<HistoryDB::Chats, SkypeDB::Chats>
//														 (source.chatname, SkypeDB::Chats::Name == source.chatname).id);
//						dest.sender_id = static_cast<int>(getOrCreate<HistoryDB::Users, SkypeDB::Contacts>
//														 (source.author  , SkypeDB::Contacts::Skypename == source.author).id);

						dest.update();
					});
					m_watching_bound_line = newBound;
					//cout << "New message detected; latest index: " << m_watching_bound_line << endl;
				}
			}));
		}
		m_w->start();
	}
	void stop() {
		if (!m_w.get()) {
			return;
		}
		m_w->stop();
	}
	void setWatchFile(std::string &&str) {
		if (str == m_filename) {
			return;
		}
		m_w.reset(nullptr);
		m_filename = str;

	}
	uint check_bound() {
		SelectQuery q;
		q.result("max(id)");
		q.source(SkypeDB::Messages::table__);
		std::lock_guard<Boss::Mutex> lock(m_mutex);
		return atoi(skype_main->query(q)[0][0]);
	}

	int calcPercent(int cnt, int i) {
	    int offset = 9;
	    double status_move = (cnt - i) << offset;
	    double percentage = status_move / cnt;
	    int status_res = static_cast<int>(percentage * 100) >> offset;

	    return status_res;
	}

	template<typename T = void>
	void import() {
		std::unordered_map<std::string, std::string> chats_hash, contacts_hash;
		auto contacts_cursor = select<SkypeDB::Contacts>(*skype_main).cursor();
		cout << "Create users base" << endl;
		history_db->begin();
		for (;contacts_cursor.rowsLeft();contacts_cursor++) {
			SkypeDB::Contacts ctc = *contacts_cursor;
			contacts_hash.emplace(ctc.skypename, ctc.fullname);
			HistoryDB::Users hu = convert<SkypeDB::Contacts, HistoryDB::Users>(ctc);
			hu.update();
			cache_element<HistoryDB::Users>(std::move(hu));
		}
		history_db->commit();

		SelectQuery q;
		q.result("count(*)");
		q.source(SkypeDB::Messages::table__);
		auto cnt = atoi(skype_main->query(q)[0][0]);
		auto i = cnt;
		int percent = 0;
		int cut = 20;
		int package = 2;
		cout << "Importing skype messages" << endl;
		auto messages_cursor = select<SkypeDB::Messages>(*skype_main).orderBy(SkypeDB::Messages::Timestamp, false).cursor();
		for (;messages_cursor.rowsLeft();messages_cursor++) {
			int asc_cnt = cnt - i;
			int test1 = (asc_cnt % package);
			if (!test1) {
				history_db->begin();
				cout << "Transactioin start" << endl;
			}
			SkypeDB::Messages sky_mes = *messages_cursor;
			percent = calcPercent(cnt, i);
			cout << "\r" << percent << "%" << flush;
			HistoryDB::Messages hm = convert<SkypeDB::Messages, HistoryDB::Messages>(sky_mes);
			hm.update();

			int tst2 = asc_cnt % (package);
			if (!(tst2 - 1) && asc_cnt) {
				history_db->commit();
				cout << "Commit" << endl;
			}
			--i;
			if (!--cut) {
//				break;
			}
		}
		cout << endl << "Succeeded!" << endl;
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

	template<typename T>
	using DBCache = std::unordered_map<std::string, T>;

	void cacheHistoryDB() {
		cache_m<HistoryDB::Chats>();
		cache_m<HistoryDB::Users>();
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
			std::get<DBCache<T>>(m_hash).emplace(row.*method, std::move(row));
		});
	}

	template<typename T>
	void cache_element(T &&element) {
		auto method = element.cache_field();
		std::get<DBCache<T>>(m_hash).emplace(element.*method, element);
	}
	template<typename From, typename To>
	To convert(const From &);

private:
	DBControllerImpl *q;
	std::string m_filename;
	std::unique_ptr<sm::filewatcher> m_w = nullptr;
	atomic_int m_watching_bound_line;
	Boss::Mutex m_mutex;
	std::unique_ptr<SkypeDB::main> skype_main;
	std::unique_ptr<HistoryDB::history> history_db;
	std::tuple< DBCache<HistoryDB::Chats>,
			    DBCache<HistoryDB::Users> > m_hash;
}; //class DBControllerImplPrivate

template<>
HistoryDB::Messages DBControllerImplPrivate::convert(const SkypeDB::Messages &source) {
	HistoryDB::Messages dest(*history_db);
	dest.skype_id = (int)source.id;
	dest.timestamp = (int)time(nullptr);
	dest.skype_timestamp = (int)source.timestamp;
	dest.body = conv_body(source.body_xml);
	dest.chat_id = static_cast<int>(getOrCreate<HistoryDB::Chats, SkypeDB::Chats>
							       (source.chatname, SkypeDB::Chats::Name == source.chatname).id);

	return std::move(dest);
}

template<>
HistoryDB::Chats DBControllerImplPrivate::convert(const SkypeDB::Chats &source) {
	HistoryDB::Chats dest(*history_db);
	dest.name = static_cast<std::string>(source.name);
	dest.owner= static_cast<std::string>(source.friendlyname);
	dest.creationtime = static_cast<int>(source.timestamp);

	return std::move(dest);
}

template<>
HistoryDB::Users DBControllerImplPrivate::convert(const SkypeDB::Contacts &source) {
	HistoryDB::Users dest(*history_db);
	dest.name = static_cast<std::string>(source.skypename);
	dest.lastmessagetime = static_cast<int>(source.lastused_timestamp);

	return std::move(dest);
}

DBControllerImpl::DBControllerImpl()
	: d(new DBControllerImplPrivate(this)) {

}

DBControllerImpl::~DBControllerImpl() {
}

Boss::RetCode BOSS_CALL DBControllerImpl::Import() {
	cout << "DBControllerImpl::Import()" << endl;
	d->import();
	return Boss::Status::Ok;
}

Boss::RetCode BOSS_CALL DBControllerImpl::SetWatchFile(Boss::IString *p_str) {
	d->setWatchFile(StringHelper(p_str).GetString<IString::AnsiString>());
	return Boss::Status::Ok;
}
Boss::RetCode BOSS_CALL DBControllerImpl::GetWatchFile(Boss::IString **pptr) {
	RefObjPtr<IString> str = Base<String>::Create(d->m_filename);
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

Boss::RetCode BOSS_CALL DBControllerImpl::AddObserver() {
	std::cout << "DBWatcherImpl::AddObserver()" << std::endl;
	return Boss::Status::Ok;
}
Boss::RetCode BOSS_CALL DBControllerImpl::RemoveObserver() {
	std::cout << "DBWatcherImpl::RemoveObserver()" << std::endl;
	return Boss::Status::Ok;
}

} //namespace skype_sc
