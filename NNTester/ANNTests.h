#pragma once
#include <vector>
#include <climits>
#include <iostream>

class GeneticAlgorithm;
class Neuron;
class NeuronNet;

class ANNTests {

	void learnPopulation(GeneticAlgorithm &ga, const std::vector<double> &inputs, const std::vector<double> &expected);

	void learnNN(NeuronNet* pNN, const std::vector<double> &inputs, const std::vector<double> &expected);

	std::vector<double> predict(GeneticAlgorithm &ga, const std::vector<double> &inputs);

public:
	ANNTests() {}

	void testRandomRange();

	void test1();
};

