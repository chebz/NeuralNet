#pragma once
#include "stdafx.h"

struct NeuralNetSettings;

class NeuralNetFactory : public PoolableFactory
{
	const NeuralNetSettings &mNNSettings;

public:
	NeuralNetFactory(const NeuralNetSettings &nnSettings);
	
	Poolable *create(ObjectPool &pool) const;
};

