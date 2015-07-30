#pragma once
#include "stdafx.h"

struct NeuronLayerSettings;

class NeuronLayerFactory : public PoolableFactory {
	const NeuronLayerSettings &mLayerSettings;

public:
	NeuronLayerFactory(const NeuronLayerSettings &layerSettings);

	Poolable *create(ObjectPool &pool) const;
};

