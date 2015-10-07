#include "DBWatcherImpl.h"

#include "core/error_codes.h"
#include <iostream>
#include "common/filewatcher.h"
#include "common/string.h"

namespace skype_sc {

class DBWatcherImplPrivate {
	friend class DBWatcherImpl;
	DBWatcherImplPrivate(DBWatcherImpl *p_q) : q(p_q) {
	}

private:
	DBWatcherImpl *q;
};

DBWatcherImpl::DBWatcherImpl()
	: d(new DBWatcherImplPrivate(this)) {

}

DBWatcherImpl::~DBWatcherImpl() {
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
