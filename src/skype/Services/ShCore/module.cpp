#include "plugin/module.h"

#include "DBCtrlImp.h"
#include "DBEventImpl.h"
#include "DBObserverImpl.h"
#include "SettingsImpl.h"
#include "PlatformUtilsImpl.h"

namespace
{
  typedef std::tuple
    <
	  skype_sc::DBControllerImpl,
      skype_sc::DBObserverImpl,
	  skype_sc::DBEventImpl,
	  skype_sc::SettingsImpl,
	  skype_sc::PlatformUtilsImpl
      >
    ExportedCoClasses;
}

BOSS_DECLARE_MODULE_ENTRY_POINT("skype_sc_core", ExportedCoClasses)
