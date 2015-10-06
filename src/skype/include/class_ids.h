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
    	DBEvent    = 0x19840a6f, // CRC32(skype_sc.service.id.DBEvent),
        DBWatcher  = 0xb1ac99c0, // CRC32(skype_sc.service.id.DBWatcher),
        DBObserver = 0xdf684aeb  // CRC32(skype_sc.service.id.DBObserver)
      };
    }
  }
}

#endif  // !__SKYPE_SC_CLASS_IDS_H__
