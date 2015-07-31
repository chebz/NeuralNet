#include "ObjectPool.h"

ObjectPool::ObjectPool(const PoolableFactory &pFactory, int numObjects) {
	for (size_t iObject = 0; iObject < numObjects; iObject++) {
		mObjectsFree.push(pFactory.create(this));
	}
}

ObjectPool::~ObjectPool() {
	while (mObjectsFree.size() > 0) {
		delete getInstance();
	}
}

void ObjectPool::free(Poolable &pPoolable) {
	mObjectsFree.push(&pPoolable);
}

Poolable* ObjectPool::getInstance() {
	if (mObjectsFree.size() == 0)
		return nullptr;

	auto pObject = mObjectsFree.top();
	mObjectsFree.pop();
	pObject->mFree = false;
	return pObject;
}