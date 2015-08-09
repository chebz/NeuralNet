#include "Poolable.h"

Poolable::Poolable(ObjectPool &pool) : mPool(pool), mFree(true) {}

void Poolable::free() {
	if (!mFree) {
		mFree = true;
		mPool.freeInstance(*this);
	}
}

ObjectPool &Poolable::getPool() {
	return mPool;
}