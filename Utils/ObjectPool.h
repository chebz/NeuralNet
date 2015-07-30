#pragma once
#include <stack>

#include "Poolable.h"
#include "PoolableFactory.h"

class ObjectPool
{
	friend class Poolable;

	std::stack<Poolable*> mObjectsFree;

	void free(Poolable &pPoolable);

public:
	ObjectPool(const PoolableFactory &pFactory, int numObjects);

	virtual ~ObjectPool();

	Poolable* getInstance();
};

