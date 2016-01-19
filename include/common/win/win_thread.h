#ifndef __WIN_THREAD_H__
#define __WIN_THREAD_H__

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include <windows.h>

#include "../callback.h"
#include "../exceptions.h"

namespace Boss
{

  BOSS_DECLARE_RUNTIME_EXCEPTION(Thread)

  namespace Internal
  {

    class ThreadImpl
    {
    public:
      ThreadImpl(ICallbackPtr callback)
        : Thread(0)
        , Callback(callback)
      {
        if (!Callback.Get())
          throw ThreadException("Empty callback");
        DWORD Id = 0;
        if (!(Thread = CreateThread(0, 0, &ThreadImpl::ThreadFunc, Callback.Get(), 0, &Id)))
          throw ThreadException("Can't create thread");
      }
      ~ThreadImpl()
      {
        WaitForSingleObject(Thread, INFINITE);
        CloseHandle(Thread);
      }

    private:
      HANDLE Thread;
      ICallbackPtr Callback;
      static DWORD CALLBACK ThreadFunc(PVOID param)
      {
        reinterpret_cast<ICallback *>(param)->Do();
        return 0;
      }
    };

  }

  typedef Internal::ThreadImpl Thread;

}

#endif  // !__WIN_THREAD_H__
