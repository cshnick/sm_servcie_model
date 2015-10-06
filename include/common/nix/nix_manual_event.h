#ifndef __NIX_MANUAL_EVENT_H__
#define __NIX_MANUAL_EVENT_H__

#include <pthread.h>

#include "../exceptions.h"


namespace Boss
{
BOSS_DECLARE_RUNTIME_EXCEPTION(ManualEvent)
namespace Private
{
class ManualEventImpl {
	ManualEventImpl(const ManualEventImpl&) = delete;
	ManualEventImpl& operator=(const ManualEventImpl&) = delete;

public:
	ManualEventImpl()
	: Flag(true) {
		if(pthread_mutex_init(&Mtx, 0)) {
						throw ManualEventException("Can't create manual event");
		}
		if (pthread_cond_init(&CondVar, 0)) {
			pthread_mutex_destroy(&Mtx);
						throw ManualEventException("Can't create manual event");
		}
	}
	~ManualEventImpl() {
		pthread_mutex_destroy(&Mtx);
		pthread_cond_destroy(&CondVar);
	}
	void Set() {
		if (pthread_mutex_lock(&Mtx)) {
			throw ManualEventException("Can't set event");
		}
		bool OldFalg = Flag;
		Flag = true;
		if (pthread_cond_broadcast(&CondVar)) {
			Flag = OldFalg;
			pthread_mutex_unlock(&Mtx);
			throw ManualEventException("Can't set event");
		}
		pthread_mutex_unlock(&Mtx);
	}
	void Reset() {
		if (pthread_mutex_lock(&Mtx)) {
			throw ManualEventException("Can't reset event");
		}
		Flag = false;
		pthread_mutex_unlock(&Mtx);
	}
	bool Wait(unsigned long timeout = -1) {
		if (pthread_mutex_lock(&Mtx)) {
			throw ManualEventException("Error wait event");
		}
		if(!Flag) {
			pthread_mutex_unlock(&Mtx);
			if(pthread_cond_wait(&CondVar, &Mtx)) {
				throw ManualEventException("Error wait event");
			}
		}
		pthread_mutex_unlock(&Mtx);
		return true;
	}

private:
	pthread_mutex_t Mtx;
	pthread_cond_t CondVar;
	bool Flag;
};
} //namespace Private
typedef Private::ManualEventImpl ManualEvent;
} //namespace Boss

#endif  // !__NIX_MANUAL_EVENT_H__
