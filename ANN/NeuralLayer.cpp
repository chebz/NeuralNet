#include "NeuronLayer.h"

NeuronLayer::NeuronLayer(ObjectPool &pool, const NeuronLayerSettings &settings) :
Poolable(pool), ObjectPool(settings.mNeuronFactory, settings.mNumNeuronsPerLayerMax), mSettings(settings) {

}

NeuronLayer::~NeuronLayer() {
	for (auto pNeuron : mNeurons) {
		delete pNeuron;
	}
}

Neuron &NeuronLayer::addNeuron() {
	Neuron* pNeuron = dynamic_cast<Neuron*>(getInstance());
	assert(pNeuron);
	mNeurons.push_back(pNeuron);
	return *pNeuron;
}

Neuron *NeuronLayer::getNeuron(int iNeuron) const {
	if (mNeurons.size() > iNeuron)
		return mNeurons[iNeuron];
	return nullptr;
}

int NeuronLayer::init(int numInputsPerNeuron) {
	int numNeurons = UTILS.randomRange(mSettings.mNumNeuronsPerLayerMin, mSettings.mNumNeuronsPerLayerMax);
	init(numInputsPerNeuron, numNeurons);	
	return numNeurons;
}

int NeuronLayer::init(int numInputsPerNeuron, int numNeurons) {
	for (int iNeuron = 0; iNeuron < numNeurons; iNeuron++) {
		addNeuron().init(numInputsPerNeuron);
	}
	return numNeurons;
}

int NeuronLayer::init(int numInputsPerNeuron, const NeuronLayer *parent, double mutationRate) {
	if (parent) {
		int numNeurons = clamp(parent->mNeurons.size() + neuronMutation(), mSettings.mNumNeuronsPerLayerMin, mSettings.mNumNeuronsPerLayerMax);
		for (int iNeuron = 0; iNeuron < numNeurons; iNeuron++) {
			addNeuron().init(numInputsPerNeuron, parent->getNeuron(iNeuron), mutationRate);
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

	int numNeurons = UTILS.randomRange(static_cast<int>(mum->mNeurons.size()), static_cast<int>(dad->mNeurons.size())) + neuronMutation();
	return init(numInputsPerNeuron, numNeurons, *mum, *dad, mutationRate);
}

int NeuronLayer::init(int numInputsPerNeuron, int numNeurons, const NeuronLayer &mum, const NeuronLayer &dad, double mutationRate) {
	int iSplit = UTILS.random(numNeurons);

	for (int iNeuron = 0; iNeuron < numNeurons; iNeuron++) {
		if (iNeuron < iSplit)
			addNeuron().init(numInputsPerNeuron, mum.getNeuron(iNeuron), mutationRate);
		else
			addNeuron().init(numInputsPerNeuron, dad.getNeuron(iNeuron), mutationRate);
	}
	return numNeurons;
}

void NeuronLayer::update(const std::vector<Neuron*> &inputs) {
	for (auto pNeuron : mNeurons) {
		pNeuron->update(inputs);
	}
}