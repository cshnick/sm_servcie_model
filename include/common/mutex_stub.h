#ifndef __mutex_stub_h__
#define __mutex_stub_h__

namespace Boss
{
class MutexStub {
	MutexStub(const MutexStub&) = delete;
	MutexStub& operator=(const MutexStub&) = delete;

public:
	void lock() {}
	void unlock() {}
};

} //namespace Boss

#endif  // !__mutex_stub_h__
