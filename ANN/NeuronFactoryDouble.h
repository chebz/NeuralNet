#pragma once
#include "NeuronFactory.h"
#include "NeuronDouble.h"

struct NeuronDoubleSettings;

class NeuronFactoryDouble :	public NeuronFactory {
	const NeuronDoubleSettings *mSettings;

public:
	NeuronFactoryDouble(const NeuronDoubleSettings *settings);

	Poolable *create(ObjectPool &pool) const;
};

