#ifndef SRC_SKYPE_SERVICES_CORE_DBOBSERVERIMPL_H_
#define SRC_SKYPE_SERVICES_CORE_DBOBSERVERIMPL_H_

#include "../../include/ifaces.h"
#include "../../include/class_ids.h"
#include "core/co_class.h"

namespace skype_sc {

class DBObserverImpl
 :public Boss::CoClass<skype_sc::service::id::DBObserver, IDBObserver> {
	DBObserverImpl();
	virtual ~DBObserverImpl();
};

#endif /* SRC_SKYPE_SERVICES_CORE_DBOBSERVERIMPL_H_ */
