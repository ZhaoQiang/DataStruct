#ifndef CATOMICLOCK_H_
#define CATOMICLOCK_H_

#include <atomic>



namespace NSAtomicLock
{
	using namespace std;
	typedef atomic<uint32_t> AtomicLock;

#define LOCKED 	 0
#define UNLOCKED 1

#define INIT_LOCK_UNLOCKED(_atomicLock) \
		{ \
	_atomicLock.store(UNLOCKED); \
		}

#define INIT_LOCK_LOCKED(_atomicLock) \
		{ \
	_atomicLock.store(LOCKED); \
		}

#define LOCK(_atomicLock) \
{ \
	uint32_t _expect=UNLOCKED; \
	while(!_atomicLock.compare_exchange_strong(_expect, LOCKED)) \
	{ \
		_expect=UNLOCKED; \
	} \
}

#define UNLOCK(_atomicLock) \
		{ \
	_atomicLock.store(UNLOCKED); \
		}
}
#endif //CATOMICLOCK_H_

