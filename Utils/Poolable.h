#pragma once
#include "ObjectPool.h"

class ObjectPool;

class Poolable {
	friend class ObjectPool;

	ObjectPool &mPool;

	bool mFree;

public:
	Poolable(ObjectPool &pool);

	virtual void free();

	ObjectPool &getPool();
};

