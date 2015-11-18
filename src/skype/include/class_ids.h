#ifndef __SKYPE_SC_CLASS_IDS_H__
#define __SKYPE_SC_CLASS_IDS_H__

#include "core/utils.h"

namespace skype_sc
{
  namespace service
  {
    namespace id
    {
      enum
      {
    	/*DBControler= Boss::MakeId("skype_sc.service.id.DBController"), //0x7ff4096
    	DBWatcher  = Boss::MakeId("skype_sc.service.id.DBWatcher"),    //0xb1ac99c0
		DBObserver = Boss::MakeId("skype_sc.service.id.DBObserver"),   //0xdf684aeb
		DBEvent    = Boss::MakeId("skype_sc.service.id.DBEvent"),      //0x19840a6f*/
    	  PlatformUtils = 0x3ed47e68, //skype_sc.service.id.PlatformUtils
    	  DBControler   = 0x7ff4096,
          DBWatcher     = 0xb1ac99c0,
          DBObserver    = 0xdf684aeb,
          DBEvent       = 0x19840a6f,
		  Settings      = 0x24a171aa, //skype_sc.service.id.Settings
      };
    }
  }
}

#endif  // !__SKYPE_SC_CLASS_IDS_H__
