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
    	DBEvent    = Boss::MakeId("skype_sc.service.id.DBEvent"),   //0x19840a6f
        DBWatcher  = Boss::MakeId("skype_sc.service.id.DBWatcher"), //0xb1ac99c0
        DBObserver = Boss::MakeId("skype_sc.service.id.DBObserver") //0xdf684aeb
      };
    }
  }
}

#endif  // !__SKYPE_SC_CLASS_IDS_H__
