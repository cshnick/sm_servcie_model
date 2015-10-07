#ifndef SRC_SKYPE_SERVICES_SHCORE_DBWATCHERIMPL_H_
#define SRC_SKYPE_SERVICES_SHCORE_DBWATCHERIMPL_H_

#include "../../include/ifaces.h"
#include "../../include/class_ids.h"
#include "core/co_class.h"

#include <memory>

namespace skype_sc {

class DBWatcherImplPrivate;
class DBWatcherImpl
 :public Boss::CoClass <skype_sc::service::id::DBWatcher, IDBWatcher, IService> {

 public:
	DBWatcherImpl();
	virtual ~DBWatcherImpl();

	virtual Boss::RetCode BOSS_CALL SetWatchFile(Boss::IString *);
	virtual Boss::RetCode BOSS_CALL GetWatchFile(Boss::IString **);

	virtual Boss::RetCode BOSS_CALL Start() override;
	virtual Boss::RetCode BOSS_CALL Stop() override;

	virtual Boss::RetCode BOSS_CALL AddObserver() override;
	virtual Boss::RetCode BOSS_CALL RemoveObserver() override;

 private:

	friend class DBWatcherImplPrivate;
	std::unique_ptr<DBWatcherImplPrivate> d;
};

} //namespace skype_sc

#endif /* SRC_SKYPE_SERVICES_SHCORE_DBWATCHERIMPL_H_ */
