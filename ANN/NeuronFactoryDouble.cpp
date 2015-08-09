#include "NeuronFactoryDouble.h"

NeuronFactoryDouble::NeuronFactoryDouble(const NeuronDoubleSettings *settings) : NeuronFactory(), mSettings(settings) {}


Poolable *NeuronFactoryDouble::create(ObjectPool &pool) const {
	NeuronDouble *n = new NeuronDouble(pool, *mSettings);
	return n;
}
