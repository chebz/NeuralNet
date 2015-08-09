#include "NeuronLayer.h"
#include "NeuronNetSettings.h"

NeuronLayer::NeuronLayer(ObjectPool &pool, const NeuronLayerSettings &settings) :
Poolable(pool), ObjectPool(settings.mNSettings.mFactory, settings.mNumNeuronsPerLayerMax), mSettings(settings) {

}

NeuronLayer::~NeuronLayer() {
	for (auto pNeuron : mpNeurons) {
		delete pNeuron;
	}
}

Neuron &NeuronLayer::addNeuron() {
	Neuron* pNeuron = dynamic_cast<Neuron*>(getInstance());
	assert(pNeuron);
	mpNeurons.push_back(pNeuron);
	return *pNeuron;
}

Neuron *NeuronLayer::getNeuron(int iN) const {
	if (mpNeurons.size() > iN)
		return mpNeurons[iN];
	return nullptr;
}

int NeuronLayer::init(int numInputsPerNeuron) {
	int numNeurons = UTILS.randomRange(mSettings.mNumNeuronsPerLayerMin, mSettings.mNumNeuronsPerLayerMax);
	init(numInputsPerNeuron, numNeurons);	
	return numNeurons;
}

int NeuronLayer::init(int numInputsPerNeuron, int numNeurons) {
	for (int iN = 0; iN < numNeurons; iN++) {
		addNeuron().init(numInputsPerNeuron);
	}
	return numNeurons;
}

int NeuronLayer::init(int numInputsPerNeuron, const NeuronLayer *parent, double mutationRate) {
	if (parent) {
		int numNeurons = clamp(parent->mpNeurons.size() + NMutation(), mSettings.mNumNeuronsPerLayerMin, mSettings.mNumNeuronsPerLayerMax);
		for (int iN = 0; iN < numNeurons; iN++) {
			addNeuron().init(numInputsPerNeuron, parent->getNeuron(iN), mutationRate);
		}
		return numNeurons;
	}		
	return init(numInputsPerNeuron);
}

int NeuronLayer::init(int numInputsPerNeuron, const NeuronLayer *mum, const NeuronLayer *dad, double mutationRate) {
	if (!mum && dad)
		return init(numInputsPerNeuron, dad, mutationRate);

	if (mum && !dad)
		return init(numInputsPerNeuron, mum, mutationRate);

	if (!mum && !dad)
		return init(numInputsPerNeuron);

	int numNeurons = UTILS.randomRange(static_cast<int>(mum->mpNeurons.size()), static_cast<int>(dad->mpNeurons.size())) + NMutation();
	return init(numInputsPerNeuron, numNeurons, *mum, *dad, mutationRate);
}

int NeuronLayer::init(int numInputsPerNeuron, int numNeurons, const NeuronLayer &mum, const NeuronLayer &dad, double mutationRate) {
	int iSplit = UTILS.random(numNeurons);

	for (int iN = 0; iN < numNeurons; iN++) {
		if (iN < iSplit)
			addNeuron().init(numInputsPerNeuron, mum.getNeuron(iN), mutationRate);
		else
			addNeuron().init(numInputsPerNeuron, dad.getNeuron(iN), mutationRate);
	}
	return numNeurons;
}

void NeuronLayer::update(const std::vector<double> &inputs) {
	for (auto pNeuron : mpNeurons) {
		pNeuron->update(inputs);
	}
}

const std::vector<double> NeuronLayer::getOutputs() const {
	std::vector<double> outputs;
	for (auto pNeuron : mpNeurons) {
		outputs.push_back(pNeuron->getValue());
	}
	return outputs;
}

void NeuronLayer::free() {
	for (auto pNeuron : mpNeurons) {
		pNeuron->free();
	}
	mpNeurons.clear();
}