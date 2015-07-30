#include "Poolable.h"

Poolable::Poolable(ObjectPool &pool) : mPool(pool), mFree(true) {}

void Poolable::free() {
	if (!mFree) {
		mFree = true;
		mPool.free(*this);
	}
}

ObjectPool &Poolable::getPool() {
	return mPool;
}