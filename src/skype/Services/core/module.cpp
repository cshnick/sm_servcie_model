#include "DBWatcherImpl.h"
#include "DBObserverImpl.h"
#include "DBEventImpl.h"

#include "plugin/module.h"

namespace
{
  
  typedef std::tuple
    <
      skype_sc::DBObserverImpl,
      skype_sc::DBEventImpl,
	  skype_sc::DBWatcherImpl
    >
    ExportedCoClasses;

}

BOSS_DECLARE_MODULE_ENTRY_POINT("skype_sc_core", ExportedCoClasses)
