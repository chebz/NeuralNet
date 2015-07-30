#include "Neuron.h"

Neuron::Neuron(ObjectPool &pool, const NeuronSettings &settings) : Poolable(pool), mSettings(settings) {}

double Neuron::getWeight(int iWeight) const {
	if (mWeights.size() > iWeight)
		return mWeights[iWeight];
	return 0;
}

double Neuron::mutate(double weight, double mutationRate) {
	if (Utils::getInstance().random01() < mutationRate) {
		weight += Utils::getInstance().randomRange(-mSettings.mWeightPerturbation, mSettings.mWeightPerturbation);
	}
	return weight;
}

void Neuron::init(int numInputsPerNeuron) {
	for (int iInput = 0; iInput < numInputsPerNeuron; iInput++) {
		mWeights.push_back(Utils::getInstance().random01());
	}
}

void Neuron::init(int numInputsPerNeuron, const Neuron *parent, double mutationRate) {
	if (parent) {
		for (int iInput = 0; iInput < numInputsPerNeuron; iInput++) {
			mWeights.push_back(mutate(parent->getWeight(iInput), mutationRate));
		}
	}
	else {
		for (int iInput = 0; iInput < numInputsPerNeuron; iInput++) {
			mWeights.push_back(mutate(0, mutationRate));
		}
	}
}

void Neuron::update(const std::vector<Neuron*> &inputs) {
	reset();
	int iWeight = 0;

	for (auto pNeuron : inputs) {
		addNeuron(pNeuron, mWeights[iWeight++]);
	}

	stepFunction();
}