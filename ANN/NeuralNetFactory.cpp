#include "NeuralNetFactory.h"


NeuralNetFactory::NeuralNetFactory(const NeuralNetSettings &nnSettings) :
PoolableFactory(), mNNSettings(nnSettings) { }

Poolable *NeuralNetFactory::create(ObjectPool &pool) const {
	NeuralNet *nn = new NeuralNet(pool, mNNSettings);
	return nn;
}