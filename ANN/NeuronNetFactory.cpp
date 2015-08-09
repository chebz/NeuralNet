#include "NeuronNetFactory.h"
#include "NeuronNetSettings.h"
#include "NeuronNet.h"

NeuronNetFactory::NeuronNetFactory(const NeuronNetSettings &nnSettings) :
	GenomeFactory(nnSettings) {}

Poolable *NeuronNetFactory::create(ObjectPool &pool) const {
	auto nnSettings = dynamic_cast<const NeuronNetSettings&>(mSettings);
	NeuronNet *nn = new NeuronNet(pool, nnSettings);
	return nn;
}