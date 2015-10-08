#include "DBWatcherImpl.h"

#include "core/error_codes.h"
#include "core/ref_obj_qi_ptr.h"
#include <iostream>
#include "common/filewatcher.h"
#include "common/string.h"
#include "common/string_helper.h"

using Boss::RefObjPtr;
using Boss::RefObjQIPtr;
using Boss::IString;
using Boss::String;
using Boss::StringHelper;
using Boss::Base;

namespace skype_sc {

class DBWatcherImplPrivate {
	friend class DBWatcherImpl;
	DBWatcherImplPrivate(DBWatcherImpl *p_q)
		: q(p_q) {
	}
	void start() {
		std::cout << "Mv.get" << m_w.get() << std::endl;
		if (!m_w.get()) {
			m_w.reset(new sm::filewatcher(m_filename, [](std::string file, int mode) {
				std :: cout << file << "; mode: "<< (mode == sm::filewatcher::e_modify ? "modify" : "access") << std::endl;
			}));
		}
		m_w->start();
	}
	void stop() {
		m_w->stop();
	}
	void setWatchFile(std::string &&str) {
		if (str == m_filename) {
			return;
		}
		m_w.reset(nullptr);
		m_filename = str;
	}

private:
	DBWatcherImpl *q;
	std::string m_filename;
	std::unique_ptr<sm::filewatcher> m_w = nullptr;
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
