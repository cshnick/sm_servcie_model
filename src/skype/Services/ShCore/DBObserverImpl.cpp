#include "DBObserverImpl.h"

#include "core/error_codes.h"
#include <iostream>
#include "common/sm_debug.h"

namespace skype_sc {

DBObserverImpl::DBObserverImpl() {
	// TODO Auto-generated constructor stub
}
DBObserverImpl::~DBObserverImpl() {
	// TODO Auto-generated destructor stub
}

Boss::RetCode BOSS_CALL DBObserverImpl::ReactOnDbChanged(IDBEvent*) {
	sm::dcout << "DBObserverImpl::ReactOnDbChanged" << std::endl;
	return Boss::Status::Ok;
}
} // namespace skype_sc
