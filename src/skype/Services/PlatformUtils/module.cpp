#include "plugin/module.h"

#include "PlatformUtilsImpl.h"

namespace
{
  typedef std::tuple
    <
	  skype_sc::PlatformUtilsImpl
    >
    ExportedCoClasses;
}

BOSS_DECLARE_MODULE_ENTRY_POINT("skype_sc_pu", ExportedCoClasses)
