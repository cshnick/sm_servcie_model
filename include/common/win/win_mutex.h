#ifndef __WIN_MUTEX_H__
#define __WIN_MUTEX_H__

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include <windows.h>

namespace Boss {
	namespace Private {
		class MutexImpl {
			MutexImpl(const MutexImpl &) = delete;
			MutexImpl& operator = (const MutexImpl &) = delete;

		public:
			MutexImpl() { InitializeCriticalSection(&Section); }
			~MutexImpl() { DeleteCriticalSection(&Section); }
			void Lock() { EnterCriticalSection(&Section); }
			void UnLock() { LeaveCriticalSection(&Section); }
			void lock() { Lock(); }
			void unlock() { UnLock(); }

		private:
			CRITICAL_SECTION Section;
		};
	} //namespace Private
	typedef Private::MutexImpl Mutex;
} //namespace Boss

#endif  // !__WIN_MUTEX_H__
