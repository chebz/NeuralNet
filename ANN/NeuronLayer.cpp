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

Neuron *NeuronLayer::getNeuron(int iNeurom) const {
	if (mpNeurons.size() > iNeurom)
		return mpNeurons[iNeurom];
	return nullptr;
}

int NeuronLayer::init(int numInputsPerNeuron) {
	int numNeurons = UTILS.randomRange(mSettings.mNumNeuronsPerLayerMin, mSettings.mNumNeuronsPerLayerMax);
	init(numInputsPerNeuron, numNeurons);	
	return numNeurons;
}

int NeuronLayer::init(int numInputsPerNeuron, UINT numNeurons) {
	for (int iNeurom = 0; iNeurom < numNeurons; iNeurom++) {
		addNeuron().init(numInputsPerNeuron);
	}
	return numNeurons;
}

int NeuronLayer::init(int numInputsPerNeuron, const NeuronLayer *parent, double mutationRate) {
	if (parent) {
		UINT numNeurons = parent->mpNeurons.size() + NMutation();
		numNeurons = clamp(numNeurons, mSettings.mNumNeuronsPerLayerMin, mSettings.mNumNeuronsPerLayerMax);
		return init(numInputsPerNeuron, numNeurons, *parent, mutationRate);
	}		
	return init(numInputsPerNeuron);
}

int NeuronLayer::init(int numInputsPerNeuron, UINT numNeurons, const NeuronLayer &parent, double mutationRate) {
	for (int iNeurom = 0; iNeurom < numNeurons; iNeurom++) {
		addNeuron().init(numInputsPerNeuron, parent.getNeuron(iNeurom), mutationRate);
	}
	return numNeurons;
}

int NeuronLayer::init(int numInputsPerNeuron, const NeuronLayer *mum, const NeuronLayer *dad, double mutationRate) {
	if (!mum && dad)
		return init(numInputsPerNeuron, dad, mutationRate);

	if (mum && !dad)
		return init(numInputsPerNeuron, mum, mutationRate);

	if (!mum && !dad)
		return init(numInputsPerNeuron);

	UINT numNeurons = UTILS.randomRange(static_cast<int>(mum->mpNeurons.size()), static_cast<int>(dad->mpNeurons.size())) + NMutation();
	numNeurons = clamp(numNeurons, mSettings.mNumNeuronsPerLayerMin, mSettings.mNumNeuronsPerLayerMax);
	return init(numInputsPerNeuron, numNeurons, *mum, *dad, mutationRate);
}

int NeuronLayer::init(int numInputsPerNeuron, UINT numNeurons, const NeuronLayer &mum, const NeuronLayer &dad, double mutationRate) {
	int iSplit = UTILS.random(numNeurons);

	for (int iNeurom = 0; iNeurom < numNeurons; iNeurom++) {
		if (iNeurom < iSplit)
			addNeuron().init(numInputsPerNeuron, mum.getNeuron(iNeurom), mutationRate);
		else
			addNeuron().init(numInputsPerNeuron, dad.getNeuron(iNeurom), mutationRate);
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
	Poolable::free();
}