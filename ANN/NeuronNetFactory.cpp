#include "NeuronNetFactory.h"
#include "NeuronNetSettings.h"
#include "NeuronNet.h"

NeuronNetFactory::NeuronNetFactory(const NeuronNetSettings &nnSettings) :
	GenomeFactory(nnSettings) {}

Poolable *NeuronNetFactory::create(ObjectPool &pool) const {
	NeuronNet *nn = new NeuronNet(pool, dynamic_cast<const NeuronNetSettings&>(mSettings));
	return nn;
}