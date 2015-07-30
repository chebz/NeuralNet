#include "NeuronDouble.h"

void NeuronDouble::init(int numInputsPerNeuron) {
	mValue = 0;
	Neuron::init(numInputsPerNeuron);
}

void NeuronDouble::init(int numInputsPerNeuron, const Neuron *parent, double mutationRate) {
	mValue = 0;
	Neuron::init(numInputsPerNeuron, parent, mutationRate);
}

void NeuronDouble::reset() { 
	mValue = 0; 
}

void NeuronDouble::addNeuron(const Neuron* pNeuron, double weight) {
	auto pNeuronDouble = dynamic_cast<const NeuronDouble*>(pNeuron);

	if (!pNeuronDouble)
		return;

	mValue += pNeuronDouble->mValue;
}

void NeuronDouble::stepFunction() {
	mValue += mBiasWeight * mBias;
	mValue = 1 / (1 + exp(-mValue));
}

void NeuronDouble::cross(Neuron *pOther) {
	auto pNeuronDouble = dynamic_cast<NeuronDouble*>(pOther);

	if (!pNeuronDouble)
		return;

	double tmp = mBiasWeight;
	mBiasWeight = pNeuronDouble->mBiasWeight;
	pNeuronDouble->mBiasWeight = tmp;
	Neuron::cross(pOther);
}

void NeuronDouble::mutate(double mutationRate, double maxPerturbation) {
	if (Utils::getInstance().random01() < mutationRate) {
		mBiasWeight += Utils::getInstance().randomRange(-1.0, 1.0) * maxPerturbation;
	}
	Neuron::mutate(mutationRate, maxPerturbation);
}

Neuron* NeuronFactoryDouble::createNeuron(int numInputs) const {
	return new NeuronDouble(numInputs, mBias);
}