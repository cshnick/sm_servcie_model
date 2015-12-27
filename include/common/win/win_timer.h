#ifndef __WIN_TIMER_H__
#define __WIN_TIMER_H__

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include <windows.h>

#include "../non_copyable.h"
#include "../callback.h"
#include "../exceptions.h"


namespace Boss
{

  BOSS_DECLARE_RUNTIME_EXCEPTION(Timer)

  namespace Internal
  {

    class TimerImpl
      : private NonCopyable
    {
    public:
      TimerImpl(ICallbackPtr callback, unsigned period)
        : TimerQueue(0)
        , Timer(0)
        , Callback(callback)
      {
        if (!Callback.Get())
          throw TimerException("Empty callback");
        if ((TimerQueue = CreateTimerQueue()) == 0)
          throw TimerException("Can't create timer queue");
        if (!CreateTimerQueueTimer(&Timer, TimerQueue, &TimerImpl::TimerFunc, Callback.Get(), period, period, 0))
        {
          DeleteTimerQueue(TimerQueue);
          TimerQueue = 0;
          throw TimerException("Can't create timer");
        }  
      }
      ~TimerImpl()
      {
        DeleteTimerQueueTimer(TimerQueue, Timer, 0);
        DeleteTimerQueue(TimerQueue);
      }

    private:
      HANDLE TimerQueue;
      HANDLE Timer;
      ICallbackPtr Callback;
      static VOID CALLBACK TimerFunc(PVOID param, BOOLEAN)
      {
        reinterpret_cast<ICallback *>(param)->Do();
      }
    };

  }

  typedef Internal::TimerImpl Timer;

}

#endif  // !__WIN_TIMER_H__
