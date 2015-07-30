#pragma once
#include "Poolable.h"

class Poolable;

class PoolableFactory {

public:
	PoolableFactory() {}

	virtual Poolable *create(ObjectPool &pool) const = 0;
};