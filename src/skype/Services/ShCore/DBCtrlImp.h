#ifndef SRC_SKYPE_SERVICES_SHCORE_DBCTRLIMP_H_
#define SRC_SKYPE_SERVICES_SHCORE_DBCTRLIMP_H_

#include "../../include/ifaces.h"
#include "../../include/class_ids.h"
#include "core/co_class.h"

#include <memory>

namespace skype_sc {

class DBControllerImplPrivate;
class DBControllerImpl
 :public Boss::CoClass <skype_sc::service::id::DBControler
  	  , IDBController
	  , IDBWatcher
	  , IService> {

 public:
	DBControllerImpl();
	virtual ~DBControllerImpl();

	virtual Boss::RetCode BOSS_CALL Import() override;
	virtual Boss::RetCode BOSS_CALL Recent(Boss::IEnum **) override;
	virtual Boss::RetCode BOSS_CALL GetMessagesAsync(MessageCallback, VoidCallback) override;
	virtual Boss::RetCode BOSS_CALL SetDBPath(Boss::IString *) override;

	virtual Boss::RetCode BOSS_CALL SetWatchFile(Boss::IString *) override;
	virtual Boss::RetCode BOSS_CALL GetWatchFile(Boss::IString **) override;

	virtual Boss::RetCode BOSS_CALL Start() override;
	virtual Boss::RetCode BOSS_CALL Stop() override;
	virtual Boss::RetCode BOSS_CALL Restart(Boss::IString *, Boss::IString *) override;

	virtual Boss::RetCode BOSS_CALL AddObserver(IDBObserver *) override;
	virtual Boss::RetCode BOSS_CALL RemoveObserver(IDBObserver *obsr) override;

 private:

	friend class DBControllerImplPrivate;
	std::unique_ptr<DBControllerImplPrivate> d;
};

} //namespace skype_sc

#endif /* SRC_SKYPE_SERVICES_SHCORE_DBCTRLIMP_H_ */
