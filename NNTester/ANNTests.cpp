#include "ANNTests.h"

static double calculateFitness(double output, double expected) {
	double fitness = 0;
	double delta = abs(output - expected);
	if (delta == 0)
		return 1.0;
	return (1.0 / delta) / DBL_MAX;
}

void ANNTests::generatePopulation(const NeuronFactory &factory, const NeuralNetSettings &nnSettings, GeneticAlgorithm &ga) {
	for (int i = 0; i < mPopulationSize; i++) {
		auto nn = new NeuralNet(nnSettings, factory);
		mPopulation.push_back(nn);
		ga.addGenome(nn);
	}
}

void ANNTests::destroyPopulation() {
	for (auto pNN : mPopulation) {
		delete pNN;
	}
	mPopulation.clear();
}

void ANNTests::update(const std::vector<Neuron*> &inputs, const std::vector<double> &expectedVals) {
	for (auto pNN : mPopulation) {
		pNN->update(inputs);
		auto outputs = pNN->getOutputs();
		double fitness = pNN->getFitness();
		for (size_t ipOutput = 0; ipOutput < outputs.size(); ipOutput++) {
			double outputVal = dynamic_cast<const NeuronDouble*>(outputs[ipOutput])->getValue();
			fitness += calculateFitness(outputVal, expectedVals[ipOutput]);
		}
		pNN->setFitness(fitness);
	}
}

void ANNTests::predict(const std::vector<Neuron*> &inputs, GeneticAlgorithm &ga) {
	Genome *topGenome = *ga.getPopulation().begin();
	NeuralNet *pNN = dynamic_cast<NeuralNet*>(topGenome);
	pNN->update(inputs);
	auto outputNeurons = pNN->getOutputs();

}

void ANNTests::test1() {
	std::cout << "Running test 1...\n";

	NeuralNetSettings nnSettings;
	nnSettings.numHiddenLayers = 1;
	nnSettings.mNumInputs = 1;
	nnSettings.numNeuronsPerHidden = 1;
	nnSettings.mNumOutputs = 1;

	NeuronFactoryDouble factory(-1.0);
	GeneticAlgorithmSettings gaSettings;
	GeneticAlgorithm ga(gaSettings);

	std::cout << "Generating population...\n";
	generatePopulation(factory, nnSettings, ga);

	NeuronDouble* input1 = new NeuronDouble(0);
	std::vector<Neuron*> inputs = { input1 };	

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
	destroyPopulation();
}