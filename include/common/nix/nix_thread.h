#ifndef __NIX_THREAD_H__
#define __NIX_THREAD_H__

#include <pthread.h>

#include "../callback.h"
#include "../exceptions.h"

namespace Boss
{

BOSS_DECLARE_RUNTIME_EXCEPTION(Thread)

namespace Private
{
class ThreadImpl {
	ThreadImpl(const ThreadImpl&) = delete;
	ThreadImpl& operator=(const ThreadImpl&) = delete;
public:
	ThreadImpl(ICallbackPtr callback)
	: Callback(callback)
	, Thread(0) {
		if (!Callback.get())
			throw ThreadException("Empty callback");
		if (pthread_create(&Thread, 0, &ThreadImpl::ThreadProc, Callback.get()))
			throw ThreadException("Can't create thread");
	}
	~ThreadImpl() {
		pthread_join(Thread, 0);
		pthread_detach(Thread);
	}

private:
	ICallbackPtr Callback;
	pthread_t Thread;

	static void* ThreadProc(void *param) {
		reinterpret_cast<ICallback *>(param)->Do();
		return 0;
	}
};

} //namespace Private

typedef Private::ThreadImpl Thread;

}// namespace Boss

#endif  // !__NIX_THREAD_H__
