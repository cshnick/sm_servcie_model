#include "DBWatcherImpl.h"
#include "DBObserverImpl.h"
#include "DBEventImpl.h"

#include "plugin/module.h"

namespace
{
  
  typedef std::tuple
    <
      MyNs::Face1,
      MyNs::Face2
    >
    ExportedCoClasses;

}

BOSS_DECLARE_MODULE_ENTRY_POINT("skype_sc_core", ExportedCoClasses)
