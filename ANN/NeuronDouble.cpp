#include "NeuronDouble.h"

void NeuronDouble::init(int numInputsPerNeuron) {
	mValue = 0;
	mBiasWeight = Utils::getInstance().randomRange(-1.0, 1.0);
	Neuron::init(numInputsPerNeuron);
}

void NeuronDouble::init(int numInputsPerNeuron, const Neuron *parent, double mutationRate) {
	mValue = 0;
	auto pNeuronDouble = dynamic_cast<const NeuronDouble*>(parent);
	if (pNeuronDouble) {		
		mBiasWeight = mutate(pNeuronDouble->mBiasWeight, mutationRate);
	}
	Neuron::init(numInputsPerNeuron, parent, mutationRate);
}

void NeuronDouble::addNeuron(const Neuron* pNeuron, double weight) {
	auto pNeuronDouble = dynamic_cast<const NeuronDouble*>(pNeuron);

	if (!pNeuronDouble)
		return;

	mValue += pNeuronDouble->mValue;
}

void NeuronDouble::stepFunction() {
	mValue += mBiasWeight * static_cast<const NeuronDoubleSettings&>(mSettings).mBias;
	mValue = 1 / (1 + exp(-mValue));
}