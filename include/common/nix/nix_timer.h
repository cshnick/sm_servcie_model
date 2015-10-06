#ifndef __NIX_TIMER_H__
#define __NIX_TIMER_H__

#include <string.h>
#include <sys/time.h>
#include <sys/signal.h>
#include <pthread.h>

#include "../callback.h"
#include "../exceptions.h"

namespace Boss {

BOSS_DECLARE_RUNTIME_EXCEPTION(Timer)

namespace Private {

class TimerImpl {
	TimerImpl(const TimerImpl&) = delete;
	TimerImpl& operator=(const TimerImpl&) = delete;

public:
	TimerImpl(ICallbackPtr callback, unsigned period)
	: Callback(callback)
	, TimerId(0) {
		if (!Callback.get()) {
			throw TimerException("Empty callback");
		}

		memset(&SigEvent, 0, sizeof(SigEvent));
		memset(&Value, 0, sizeof(Value));

		Value.it_value.tv_sec = period / 1000;
		Value.it_value.tv_nsec = (period % 1000) * 1000000;

		Value.it_interval.tv_sec = period / 1000;
		Value.it_interval.tv_nsec = (period % 1000) * 1000000;

		SigEvent.sigev_notify = SIGEV_THREAD;
		SigEvent.sigev_notify_function = &TimerImpl::TimerFunc;
		SigEvent.sigev_notify_attributes = NULL;
		SigEvent.sigev_value.sival_ptr = Callback.get();

		if (timer_create(CLOCK_REALTIME, &SigEvent, &TimerId)) {
			timer_delete(TimerId);
			throw TimerException("Can't create timer");
		}

		if (timer_settime(TimerId, 0, &Value, NULL)) {
			throw TimerException("Can't set timer");
		}
	}
	~TimerImpl() {
		timer_delete(TimerId);
	}

private:
	ICallbackPtr Callback;
	sigevent SigEvent;
	timer_t TimerId;
	itimerspec Value;
	static void TimerFunc(union sigval val) {
		reinterpret_cast<ICallback*>(val.sival_ptr)->Do();
	}
};

} //namespace Private
typedef Private::TimerImpl Timer;
} //namespace Boss

#endif  // !__NIX_TIMER_H__
