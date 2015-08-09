#include "ANNTests.h"
#include "NeuronNetSettings.h"
#include "NeuronNetFactory.h"
#include "NeuronNet.h"
#include "GeneticAlgorithm.h"

static double calculateFitness(double output, double expected) {
	double fitness = 0;
	double delta = abs(output - expected);
	if (delta == 0)
		return 1.0;
	return (1.0 / delta) / DBL_MAX;
}

void ANNTests::update(GeneticAlgorithm &ga, const std::vector<Neuron*> &inputs, const std::vector<double> &expectedVals) {
	for (auto pGenome : ga.getPopulation()) {
		auto pNeuronNet = dynamic_cast<NeuronNet*>(pGenome);
		pNeuronNet->update(inputs);
		auto outputs = pNeuronNet->getOutputs();
		double fitness = pNeuronNet->getFitness();
		for (size_t ipOutput = 0; ipOutput < outputs.size(); ipOutput++) {
			double outputVal = outputs[ipOutput]->getValue();
			fitness += calculateFitness(outputVal, expectedVals[ipOutput]);
		}
		pNeuronNet->setFitness(fitness);
	}
}

void ANNTests::predict(const std::vector<Neuron*> &inputs, GeneticAlgorithm &ga) {
	/*Genome *topGenome = *ga.getPopulation().begin();
	NeuronNet *pNeuronNet = dynamic_cast<NeuronNet*>(topGenome);
	pNeuronNet->update(inputs);
	auto outputNs = pNeuronNet->getOutputs();*/

}

void ANNTests::test1() {
	std::cout << "Running test 1...\n";

	NeuronSettings nSettings;
	NeuronLayerSettings layerSettings(nSettings);
	NeuronNetSettings nnSettings(layerSettings);
	
	nnSettings.mNumInputs = 1;
	nnSettings.mNumOutputs = 1;
	nnSettings.mNumLayersMin = 1;
	nnSettings.mNumLayersMax = 1;
	nnSettings.mNumLayersPertrubation = 0;
	
	GeneticAlgorithmSettings gaSettings(nnSettings.mFactory);
	GeneticAlgorithm ga(gaSettings);

	Neuron* input1 = new Neuron(0);
	std::vector<N*> inputs = { input1 };	

	std::cout << "Learning...\n";
	for (int iEpoch = 0; iEpoch < mNumEpochs; iEpoch++) {
		std::cout << "Epoch: " << iEpoch + 1 << " / " << mNumEpochs << "\t";		

		for (int x = 0; x < 100; x++) {
			double val = static_cast<double>(x);
			input1->setValue(val);
			update(inputs, { val });
		}

		std::cout << "Average: " << ga.getAverageFitness() << "\t";
		std::cout << "Best: " << ga.getBestFitness() << "\t";
		std::cout << "Worst: " << ga.getWorstFitness() << "\n";

		ga.epoch();
	}
	std::cout << "Predicting...\n";

	
	delete input1;
}