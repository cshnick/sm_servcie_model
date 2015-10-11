#include "plugin/module.h"

#include "DBCtrlImp.h"
#include "DBEventImpl.h"
#include "DBObserverImpl.h"

namespace
{
  typedef std::tuple
    <
	  skype_sc::DBControllerImpl,
      skype_sc::DBObserverImpl,
      skype_sc::DBEventImpl
      >
    ExportedCoClasses;
}

BOSS_DECLARE_MODULE_ENTRY_POINT("skype_sc_core", ExportedCoClasses)
