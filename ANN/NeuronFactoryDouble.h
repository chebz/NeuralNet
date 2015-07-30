#pragma once
#include "NeuronFactory.h"
class NeuronFactoryDouble :	public NeuronFactory
{
public:
	NeuronFactoryDouble();

	Poolable *create(ObjectPool &pool) const;
};

