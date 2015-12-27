#ifndef __WIN_MANUAL_EVENT_H__
#define __WIN_MANUAL_EVENT_H__

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include <windows.h>

#include "../non_copyable.h"
#include "../exceptions.h"


namespace Boss
{

  BOSS_DECLARE_RUNTIME_EXCEPTION(ManualEvent)

  namespace Internal
  {

    class ManualEventImpl
      : private NonCopyable
    {
    public:
      ManualEventImpl()
        : Event(0)
      {
        if ((Event = CreateEvent(0, TRUE, TRUE, 0)) == 0)
          throw ManualEventException("Can't create event");
      }
      ~ManualEventImpl()
      {
        CloseHandle(Event);
      }
      void Set()
      {
        if (!SetEvent(Event))
          throw ManualEventException("Can't set event");
      }
      void Reset()
      {
        if (!ResetEvent(Event))
          throw ManualEventException("Can't reset event");
      }
      bool Wait(unsigned long timeout = INFINITE)
      {
        DWORD Res = WaitForSingleObject(Event, timeout);
        if (Res == WAIT_FAILED)
          throw ManualEventException("Error wait event");
        return Res == WAIT_OBJECT_0;
      }

    private:
      HANDLE Event;
    };

  }

  typedef Internal::ManualEventImpl ManualEvent;

}

#endif  // !__WIN_MANUAL_EVENT_H__
