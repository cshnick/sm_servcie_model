#ifndef __NIX_MUTEX_H__
#define __NIX_MUTEX_H__

#include <pthread.h>

#include "core/exceptions.h"

#include <memory>
#include <cstring>
#include <sstream>
#include <iostream>

namespace Boss
{
BOSS_DECLARE_RUNTIME_EXCEPTION(Mutex)
namespace Private {

class MutexImpl
{
	MutexImpl(const MutexImpl&) = delete;
	MutexImpl& operator=(const MutexImpl&) = delete;
	MutexImpl(MutexImpl&&) = delete;

public:
	MutexImpl()
	: MutexHandle(new pthread_mutex_t) {
		MutexAttr.reset(new pthread_mutexattr_t);
		memset(MutexAttr.get(), 0, sizeof(pthread_mutexattr_t));
        pthread_mutexattr_init(MutexAttr.get());
		if (pthread_mutexattr_settype(MutexAttr.get(), PTHREAD_MUTEX_RECURSIVE))
		{
			throw MutexException("Can't create mutex");
		}
		int ret = pthread_mutex_init(MutexHandle.get(), MutexAttr.get());
		if (ret) {
			std::stringstream ss;
			ss << "Can't create mutex; reason: " << strerror(ret) << "\n";
			//std::cerr << ss.str().c_str() << std::endl;
			throw MutexException(ss.str().c_str());
		}
		if (pthread_mutexattr_destroy(MutexAttr.get()))
		{
			pthread_mutex_destroy(MutexHandle.get());
			throw MutexException("Can't create mutex, error at destruction");
		}
	}
	~MutexImpl() {
		pthread_mutex_destroy(MutexHandle.get());
	}
	void lock() {
		if (pthread_mutex_lock(MutexHandle.get()))
			throw MutexException("Can't lock mutex");
	}
	void unlock() {
		if (pthread_mutex_unlock(MutexHandle.get()))
			throw MutexException("Can't unlock mutex");
	}

private:
	std::unique_ptr<pthread_mutexattr_t> MutexAttr;
	std::unique_ptr<pthread_mutex_t> MutexHandle;
};

} //namespace Private

typedef Private::MutexImpl Mutex;

} //namespace Boss

#endif  // !__NIX_MUTEX_H__
