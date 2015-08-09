#include "NeuronLayerFactory.h"
#include "NeuronLayer.h"
#include "NeuronNetSettings.h"

NeuronLayerFactory::NeuronLayerFactory(const NeuronLayerSettings &layerSettings) : 
PoolableFactory(), mLayerSettings(layerSettings) {}


Poolable *NeuronLayerFactory::create(ObjectPool &pool) const {
	return new NeuronLayer(pool, mLayerSettings);
}
