#ifndef __PULSED_THREAD_H__
#define __PULSED_THREAD_H__

#include <memory>
#include "callback.h"
#include "thread.h"
#include "timer.h"
#include "manual_event.h"
#include "mutex.h"


namespace Boss {

class PulsedThread {

	PulsedThread(const PulsedThread&) = delete;
	PulsedThread& operator=(const PulsedThread&) = delete;
public:
	PulsedThread(ICallbackPtr callback, unsigned period)
	: IsRun(true)
	, Callback(callback) {
		Event_.Reset();
		Thread_.reset(new Thread(CreateMemberCallback(*this, &PulsedThread::Loop)));
		Timer_.reset(new Timer(CreateMemberCallback(*this, &PulsedThread::Resume), period));
	}
	~PulsedThread() {
		{
			std::lock_guard<Mutex> Lock(Mutex_);
			IsRun = false;
			Event_.Set();
		}
		Thread_.reset();
	}

private:
	volatile bool IsRun;
	ICallbackPtr Callback;
	Mutex Mutex_;
	ManualEvent Event_;
	std::shared_ptr<Thread> Thread_;
	std::shared_ptr<Timer> Timer_;

	void Resume() {
		std::lock_guard<Mutex> Lock(Mutex_);
		Event_.Set();
	}

	void Loop() {
		for ( ; ; ) {
			try {
				if (IsRun) {
					Event_.Wait();
				} else {
					break;
				}
				if (IsRun) {
					Callback->Do();
				} else {
					break;
				}
				{
					std::lock_guard<Mutex> Lock(Mutex_);
					if (IsRun)
						Event_.Reset();
					else
						break;
				}
			}
			catch (std::exception &) {
			}
		}
	}
};

} //namespace Boss

#endif  // !__PULSED_THREAD_H__
