#include "DBWatcherImpl.h"

#include "core/error_codes.h"
#include <iostream>
#include "common/filewatcher.h"
#include "common/string.h"
#include "common/string_helper.h"

namespace skype_sc {

class DBWatcherImplPrivate {
	friend class DBWatcherImpl;
	DBWatcherImplPrivate(DBWatcherImpl *p_q) : q(p_q) {

	}

private:
	DBWatcherImpl *q;

	std::string m_filename;
};

DBWatcherImpl::DBWatcherImpl()
	: d(new DBWatcherImplPrivate(this)) {

}

DBWatcherImpl::~DBWatcherImpl() {
}

Boss::RetCode BOSS_CALL DBWatcherImpl::SetWatchFile(Boss::IString *p_str) {
	//std::string str = Boss::StringHelper(p_str);
	return Boss::Status::Ok;
}
Boss::RetCode BOSS_CALL DBWatcherImpl::GetWatchFile(Boss::IString **) {
	return Boss::Status::Ok;
}

Boss::RetCode BOSS_CALL DBWatcherImpl::Start() {
	std::cout << "DBWatcherImpl::Start()" << std::endl;
	return Boss::Status::Ok;
}
Boss::RetCode BOSS_CALL DBWatcherImpl::Stop() {
	std::cout << "DBWatcherImpl::Stop()" << std::endl;
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
