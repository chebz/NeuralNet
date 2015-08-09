#pragma once
#include "stdafx.h"
#include "Neuron.h"

struct NeuronSettings;

class NeuronFactory : public PoolableFactory {
	const NeuronSettings &mSettings;
public:
	NeuronFactory(const NeuronSettings &settings) : 
		PoolableFactory(), 
		mSettings(settings) {}

	Poolable *create(ObjectPool &pool) const;
};

