#include "DBWatcherImpl.h"

#include <atomic>
#include <iostream>
#include <algorithm>

#include "core/error_codes.h"
#include "core/ref_obj_qi_ptr.h"
#include "common/mutex.h"
#include "common/filewatcher.h"
#include "common/string.h"
#include "common/string_helper.h"
#include "core/exceptions.h"

#include "litesql.hpp"
#include "skype_main_db.hpp"

using Boss::RefObjPtr;
using Boss::RefObjQIPtr;
using Boss::IString;
using Boss::String;
using Boss::StringHelper;
using Boss::Base;

using std::atomic; using std::atomic_int; using std::cout; using std::endl;
using namespace litesql;

namespace skype_sc {

class DBWatcherImplPrivate {
	friend class DBWatcherImpl;
	DBWatcherImplPrivate(DBWatcherImpl *p_q)
		: q(p_q)
		, m_watching_bound_line(-1) {
	}
	void start() {
		if (m_filename.empty()) {
			std::cout << "Filename is empty, nothing to start" << std::endl;
			return;
		}
		if (!skype_main.get()) {
			try {
				skype_main.reset(new SkypeDB::main("sqlite3", std::string("database=") + m_filename));
				skype_main->verbose = true;
			} catch (const std::exception &e) {
				throw runtime_error(e.what());
			}
		}
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
					std::for_each(ms.begin(), ms.end(), [](const Messages &m) {
						cout << m.id << " - " << m.body_xml << std::endl;
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

private:
	DBWatcherImpl *q;
	std::string m_filename;
	std::unique_ptr<sm::filewatcher> m_w = nullptr;
	atomic_int m_watching_bound_line;
	Boss::Mutex m_mutex;
	std::unique_ptr<SkypeDB::main> skype_main;
};

DBWatcherImpl::DBWatcherImpl()
	: d(new DBWatcherImplPrivate(this)) {

}

DBWatcherImpl::~DBWatcherImpl() {
}

Boss::RetCode BOSS_CALL DBWatcherImpl::SetWatchFile(Boss::IString *p_str) {
	d->setWatchFile(StringHelper(p_str).GetString<IString::AnsiString>());
	return Boss::Status::Ok;
}
Boss::RetCode BOSS_CALL DBWatcherImpl::GetWatchFile(Boss::IString **pptr) {
	RefObjPtr<IString> str = Base<String>::Create(d->m_filename);
	return str.QueryInterface(pptr);
}

Boss::RetCode BOSS_CALL DBWatcherImpl::Start() {
	std::cout << "DBWatcherImpl::Start()" << std::endl;
	d->start();
	return Boss::Status::Ok;
}
Boss::RetCode BOSS_CALL DBWatcherImpl::Stop() {
	std::cout << "DBWatcherImpl::Stop()" << std::endl;
	d->stop();
	return Boss::Status::Ok;
}

Boss::RetCode BOSS_CALL DBWatcherImpl::AddObserver() {
	std::cout << "DBWatcherImpl::AddObserver()" << std::endl;
	return Boss::Status::Ok;
}
Boss::RetCode BOSS_CALL DBWatcherImpl::RemoveObserver() {
	std::cout << "DBWatcherImpl::RemoveObserver()" << std::endl;
	return Boss::Status::Ok;
}

} //namespace skype_sc
