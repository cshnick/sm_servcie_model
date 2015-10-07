#include "DBWatcherImpl.h"
#include "core/error_codes.h"
#include <iostream>

namespace skype_sc {

DBWatcherImpl::DBWatcherImpl() {
	// TODO Auto-generated constructor stub
}

DBWatcherImpl::~DBWatcherImpl() {
	// TODO Auto-generated destructor stub
}

Boss::RetCode BOSS_CALL DBWatcherImpl::AddObserver() {
	std::cout << "DBWatcherImpl::AddObserver()" << std::endl;
	return Boss::Status::Ok;
}
Boss::RetCode BOSS_CALL RemoveObserver() {
	std::cout << "DBWatcherImpl::RemoveObserver()" << std::endl;
	return Boss::Status::Ok;
}

} //namespace skype_sc
