#ifndef SRC_SKYPE_SERVICES_CORE_DBWATCHERIMPL_H_
#define SRC_SKYPE_SERVICES_CORE_DBWATCHERIMPL_H_

#include "../../include/ifaces.h"
#include "../../include/class_ids.h"
#include "core/co_class.h"

namespace skype_sc {

class DBWatcherImpl
 :public Boss::CoClass <skype_sc::service::id::DBWatcher, IDBWatcher> {

 public:
	DBWatcherImpl();
	virtual ~DBWatcherImpl();

	virtual Boss::RetCode BOSS_CALL AddObserver();
	virtual Boss::RetCode BOSS_CALL RemoveObserver();
};

} //namespace skype_sc

#endif /* SRC_SKYPE_SERVICES_CORE_DBWATCHERIMPL_H_ */
