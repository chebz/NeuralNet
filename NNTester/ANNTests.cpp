#include <functional>
#include "ANNTests.h"
#include "NeuronNetSettings.h"
#include "NeuronNetFactory.h"
#include "NeuronNet.h"
#include "GeneticAlgorithm.h"

static double calculateFitness(double output, double expected) {
	double fitness = 0;
	double delta = abs(output - expected);
	return 1 - delta;
}

void ANNTests::learnPopulation(GeneticAlgorithm &ga, const std::vector<double> &inputs, const std::vector<double> &expected) {
	for (auto pGenome : ga.getPopulation()) {
		auto pNN = dynamic_cast<NeuronNet*>(pGenome);
		learnNN(pNN, inputs, expected);
	}
}

void ANNTests::learnNN(NeuronNet* pNN, const std::vector<double> &inputs, const std::vector<double> &expected) {
	pNN->update(inputs);
	auto outputs = pNN->getOutputs();
	assert(outputs.size() == expected.size());
	double tempFitness = pNN->getFitness();
	for (size_t ipOutput = 0; ipOutput < outputs.size(); ipOutput++) {
		tempFitness += calculateFitness(outputs[ipOutput], expected[ipOutput]);
	}
	pNN->setFitness(tempFitness);
}

std::vector<double> ANNTests::predict(GeneticAlgorithm &ga, const std::vector<double> &inputs) {
	auto pNN = dynamic_cast<NeuronNet*>(*ga.getSortedPopulation().begin());
	pNN->update(inputs);
	return pNN->getOutputs();
}

void ANNTests::testRandomRange() {
	std::cout << "testing random range function...\n";

	double min = -1.0;
	double max = 1.0;
	double result = 0.0;
	double resultMin = 0.0;
	double resultMax = 0.0;

	for (int x = 0; x <= 1000; x++) {
		result = Utils::getInstance().randomRange(min, max);
		if (result > resultMax)
			resultMax = result;
		if (result < resultMin)
			resultMin = result;
		std::cout << result << "\n";
	}

	std::cout << "Min: " << resultMin << ", Max: " << resultMax << "\n";
}

void ANNTests::test1() {
	std::cout << "Running test 1...\n";

	NeuronSettings nSettings;
	NeuronLayerSettings layerSettings(nSettings);
	layerSettings.mNumNeuronsPerLayerMin = 2;
	layerSettings.mNumNeuronsPerLayerMax = 2;

	NeuronNetSettings nnSettings(layerSettings);

	nnSettings.mNumInputs = 1;
	nnSettings.mNumOutputs = 1;
	nnSettings.mNumLayersMin = 2;
	nnSettings.mNumLayersMax = 2;

	GeneticAlgorithmSettings gaSettings(nnSettings.mFactory);
	gaSettings.mMaxPopulation = 100;

	GeneticAlgorithm ga(gaSettings);

	std::vector<double> inputs = { 0 };
	std::vector<double> expected = { 0 };

	int mNumEpochs = 100;

	std::cout << "Learning...\n";
	for (int iEpoch = 0; iEpoch < mNumEpochs; iEpoch++) {
		std::cout << "Epoch: " << iEpoch + 1 << " / " << mNumEpochs << "\t";

		for (int x = 0; x <= 100; x++) {
			inputs[0] = static_cast<double>(x) / 100.0;
			expected[0] = static_cast<double>(x) / 100.0;
			learnPopulation(ga, inputs, expected);
		}

		std::cout << "Average: " << ga.getAverageFitness() << "\t";
		std::cout << "Best: " << ga.getBestFitness() << "\t";
		std::cout << "Worst: " << ga.getWorstFitness() << "\n";

		ga.epoch();
	}

	std::cout << "Predicting...\n";

	for (int x = 0; x <= 100; x++) {
		inputs[0] = static_cast<double>(x) / 100.0;
		auto outputs = predict(ga, inputs);
		std::cout << "Input:\t" << inputs[0] << "\t\tOutput:\t" << outputs[0] << "\n";
	}
}