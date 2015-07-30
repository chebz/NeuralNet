#include "NeuralNet.h"

NeuralNet::NeuralNet(ObjectPool &pool, const NeuralNetSettings &settings) :
Genome(pool), 
ObjectPool(settings.mLayerFactory, settings.mNumLayersMax), 
mSettings(settings){
	mpOutputLayer = new NeuronLayer(*this, settings.mLayerSettings);
}

NeuralNet::~NeuralNet() {
	for (auto pLayer : mLayers) {
		delete pLayer;
	}
}

NeuronLayer &NeuralNet::addLayer() {
	auto pLayer = dynamic_cast<NeuronLayer*>(getInstance());
	assert(pLayer);
	mLayers.push_back(pLayer);
	return *pLayer;
}

NeuronLayer *NeuralNet::getLayer(int iLayer) const {
	if (mLayers.size() > iLayer)
		return mLayers[iLayer];
	return nullptr;
}

void NeuralNet::init() {
	int numLayers = UTILS.randomRange(mSettings.mNumLayersMin, mSettings.mNumLayersMax);
	int numNeurons = 0;

	if (numLayers > 0) {
		numNeurons = addLayer().init(mSettings.mNumInputs);

		for (int iHiddenLayer = 0; iHiddenLayer < numLayers; iHiddenLayer++) {
			numNeurons = addLayer().init(numNeurons);
		}
				
		mpOutputLayer->init(numNeurons, mSettings.mNumOutputs);
	}
	else {
		mpOutputLayer->init(mSettings.mNumInputs, mSettings.mNumOutputs);
	}
}

void NeuralNet::init(const Genome &parent, double mutationRate) {
	auto nnParent = dynamic_cast<const NeuralNet&>(parent);

	int numLayers = nnParent.mLayers.size() + layerMutation();
	numLayers = clamp(numLayers, mSettings.mNumLayersMin, mSettings.mNumLayersMax);

	int numNeurons = 0;
	int iLayer = 0;

	if (numLayers > 0) {
		numNeurons = addLayer().init(mSettings.mNumInputs, nnParent.getLayer(iLayer), mutationRate);
		iLayer++;

		for (int iHiddenLayer = 0; iHiddenLayer < numLayers; iHiddenLayer++) {
			numNeurons = addLayer().init(numNeurons, nnParent.getLayer(iLayer), mutationRate);
			iLayer++;
		}

		addLayer().init(numNeurons, mSettings.mNumOutputs);
	}
	else {
		addLayer().init(mSettings.mNumInputs, mSettings.mNumOutputs);
	}
}

void NeuralNet::init(const Genome &mum, const Genome &dad, double mutationRate) {
	auto nnMum = dynamic_cast<const NeuralNet&>(mum);
	auto nnDad = dynamic_cast<const NeuralNet&>(dad);
	
	int numLayers = UTILS.randomRange(static_cast<int>(nnMum.mLayers.size()), static_cast<int>(nnDad.mLayers.size())) + layerMutation();
	numLayers = clamp(numLayers, mSettings.mNumLayersMin, mSettings.mNumLayersMax);

	int numNeurons = 0;
	int iLayer = 0;

	if (numLayers > 0) {
		numNeurons = addLayer().init(mSettings.mNumInputs, nnMum.getLayer(iLayer), nnDad.getLayer(iLayer), mutationRate);
		iLayer++;

		for (int iHiddenLayer = 0; iHiddenLayer < numLayers; iHiddenLayer++) {
			numNeurons = addLayer().init(numNeurons, nnMum.getLayer(iLayer), nnDad.getLayer(iLayer), mutationRate);
			iLayer++;
		}

		addLayer().init(numNeurons, mSettings.mNumOutputs);
	}
	else {
		addLayer().init(mSettings.mNumInputs, mSettings.mNumOutputs);
	}
}

void NeuralNet::update(const std::vector<Neuron*> &inputs) {
	if (inputs.size() != mSettings.mNumInputs)
		return;

	for (auto &layer : mLayers) {
		layer->update(inputs);
	}
}