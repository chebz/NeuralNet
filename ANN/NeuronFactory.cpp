#include "NeuronFactory.h"

Poolable *NeuronFactory::create(ObjectPool &pool) const {
	Neuron *n = new Neuron(pool, mSettings);
	return n;
}
