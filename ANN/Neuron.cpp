#include "Neuron.h"
#include "NeuronNetSettings.h"

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
	mBiasWeight = Utils::getInstance().randomRange(-1.0, 1.0);

	for (int iInput = 0; iInput < numInputsPerNeuron; iInput++) {
		mWeights.push_back(Utils::getInstance().randomRange(-1.0, 1.0));
	}
}

void Neuron::init(int numInputsPerNeuron, const Neuron *parent, double mutationRate) {
	if (parent) {
		mBiasWeight = mutate(parent->mBiasWeight, mutationRate);
		for (int iInput = 0; iInput < numInputsPerNeuron; iInput++) {
			mWeights.push_back(mutate(parent->getWeight(iInput), mutationRate));
		}
	}
	else {
		mBiasWeight = mutate(0, mutationRate);
		for (int iInput = 0; iInput < numInputsPerNeuron; iInput++) {
			mWeights.push_back(mutate(0, mutationRate));
		}
	}
}

void Neuron::update(const std::vector<double> &inputs) {
	assert(inputs.size() == mWeights.size());

	mValue = 0;

	for (int iInput = 0; iInput < inputs.size(); iInput++) {
		mValue += inputs[iInput] * mWeights[iInput];
	}

	mValue += mBiasWeight * mSettings.mBias;
	mValue = 1 / (1 + exp(-mValue / mSettings.mActivationResponse));
}

void Neuron::free() {
	mWeights.clear();
	Poolable::free();
}