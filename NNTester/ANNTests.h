#pragma once
#include <vector>
#include <climits>
#include <iostream>

#include "NeuronNet.h"
#include "GeneticAlgorithm.h"

class ANNTests
{
	const int mNumEpochs;

	const int mPopulationSize;

	void update(const std::vector<Neuron*> &inputs, const std::vector<double> &outputValues);

	void predict(const std::vector<Neuron*> &inputs, GeneticAlgorithm &ga);

public:
	ANNTests() : mNumEpochs(100), mPopulationSize(100) {}

	void test1();
};

