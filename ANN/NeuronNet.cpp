#include "NeuronNet.h"
#include "NeuronLayer.h"
#include "NeuronNetSettings.h"

NeuronNet::NeuronNet(ObjectPool &pool, const NeuronNetSettings &settings) :
	Genome(pool, settings), ObjectPool(settings.mLayerSettings.mFactory, settings.mNumLayersMax) {
	mpOutputLayer = new NeuronLayer(*this, settings.mLayerSettings);
}

NeuronNet::~NeuronNet() {
	for (auto pLayer : mpLayers) {
		delete pLayer;
	}
	delete mpOutputLayer;
}

NeuronLayer &NeuronNet::addLayer() {
	auto pLayer = dynamic_cast<NeuronLayer*>(getInstance());
	assert(pLayer);
	mpLayers.push_back(pLayer);
	return *pLayer;
}

NeuronLayer *NeuronNet::getLayer(int iLayer) const {
	if (mpLayers.size() > iLayer)
		return mpLayers[iLayer];
	return nullptr;
}

void NeuronNet::init() {
	auto nnSettings = dynamic_cast<const NeuronNetSettings&>(mSettings);

	int numLayers = UTILS.randomRange(nnSettings.mNumLayersMin, nnSettings.mNumLayersMax);
	int numNeurons = 0;

	if (numLayers > 0) {
		numNeurons = addLayer().init(nnSettings.mNumInputs);

		for (int iHiddenLayer = 0; iHiddenLayer < numLayers; iHiddenLayer++) {
			numNeurons = addLayer().init(numNeurons);
		}
				
		mpOutputLayer->init(numNeurons, nnSettings.mNumOutputs);
	}
	else {
		mpOutputLayer->init(nnSettings.mNumInputs, nnSettings.mNumOutputs);
	}
}

void NeuronNet::init(const Genome &parent, double mutationRate) {
	auto nnParent = dynamic_cast<const NeuronNet&>(parent);
	auto nnSettings = dynamic_cast<const NeuronNetSettings&>(mSettings);

	UINT numLayers = nnParent.mpLayers.size() + layerMutation();
	numLayers = clamp(numLayers, nnSettings.mNumLayersMin, nnSettings.mNumLayersMax);

	int numNeurons = 0;
	int iLayer = 0;

	if (numLayers > 0) {
		numNeurons = addLayer().init(nnSettings.mNumInputs, nnParent.getLayer(iLayer), mutationRate);
		iLayer++;

		for (int iHiddenLayer = 0; iHiddenLayer < numLayers; iHiddenLayer++) {
			numNeurons = addLayer().init(numNeurons, nnParent.getLayer(iLayer), mutationRate);
			iLayer++;
		}

		addLayer().init(numNeurons, nnSettings.mNumOutputs);
	}
	else {
		addLayer().init(nnSettings.mNumInputs, nnSettings.mNumOutputs);
	}
}

void NeuronNet::init(const Genome &mum, const Genome &dad, double mutationRate) {
	auto nnMum = dynamic_cast<const NeuronNet&>(mum);
	auto nnDad = dynamic_cast<const NeuronNet&>(dad);
	auto nnSettings = dynamic_cast<const NeuronNetSettings&>(mSettings);

	UINT numLayers = UTILS.randomRange(static_cast<int>(nnMum.mpLayers.size()), static_cast<int>(nnDad.mpLayers.size())) + layerMutation();
	numLayers = clamp(numLayers, nnSettings.mNumLayersMin, nnSettings.mNumLayersMax);

	int numNeurons = 0;
	int iLayer = 0;

	if (numLayers > 0) {
		numNeurons = addLayer().init(nnSettings.mNumInputs, nnMum.getLayer(iLayer), nnDad.getLayer(iLayer), mutationRate);
		iLayer++;

		for (int iHiddenLayer = 0; iHiddenLayer < numLayers; iHiddenLayer++) {
			numNeurons = addLayer().init(numNeurons, nnMum.getLayer(iLayer), nnDad.getLayer(iLayer), mutationRate);
			iLayer++;
		}

		addLayer().init(numNeurons, nnSettings.mNumOutputs);
	}
	else {
		addLayer().init(nnSettings.mNumInputs, nnSettings.mNumOutputs);
	}
}

void NeuronNet::update(std::vector<double> inputs) {
	auto nnSettings = dynamic_cast<const NeuronNetSettings&>(mSettings);

	assert(inputs.size() == nnSettings.mNumInputs);

	for (auto pLayer : mpLayers) {
		pLayer->update(inputs);
		inputs = pLayer->getOutputs();
	}
}

const std::vector<double> NeuronNet::getOutputs() const {
	return mpLayers[mpLayers.size() - 1]->getOutputs();
}

void NeuronNet::free() {
	for (auto pLayer : mpLayers) {
		pLayer->free();
	}
	mpLayers.clear();
}