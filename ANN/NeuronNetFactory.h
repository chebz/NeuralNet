#pragma once
#include "stdafx.h"

struct NeuronNetSettings;

class NeuronNetFactory : public GenomeFactory
{
public:
	NeuronNetFactory(const NeuronNetSettings &nnSettings);
	
	Poolable *create(ObjectPool &pool) const;
};

