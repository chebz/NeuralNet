#pragma once
#include "stdafx.h"

class NeuronLayerFactory;
class NeuronFactory;

struct NeuronSettings {
	double mWeightPerturbation;

	NeuronSettings() :
		mWeightPerturbation(0) {}
};

struct NeuronLayerSettings {
	UINT mNumNeuronsPerLayerMin;
	UINT mNumNeuronsPerLayerMax;
	UINT mNumNeuronsPertrubation;

	const NeuronFactory &mNeuronFactory;

	NeuronSettings mNeuronSettings;

	NeuronLayerSettings(const NeuronFactory &neuronFactory) :
		mNumNeuronsPerLayerMin(1),
		mNumNeuronsPerLayerMax(1),
		mNumNeuronsPertrubation(0),
		mNeuronFactory(neuronFactory),
		mNeuronSettings() {}
};

struct NeuralNetSettings {
	int mNumInputs;
	int mNumOutputs;
	
	int mNumLayersMin;
	int mNumLayersMax;
	int mNumLayersPertrubation;
	
	const NeuronLayerFactory &mLayerFactory;

	NeuronLayerSettings mLayerSettings;

	NeuralNetSettings(const NeuronLayerFactory &layerFactory, const NeuronFactory &neuronFactory) :
		mNumInputs(1),
		mNumOutputs(1),
		mNumLayersMin(1),
		mNumLayersMax(1),
		mNumLayersPertrubation(0),
		mLayerFactory(layerFactory),
		mLayerSettings(neuronFactory) {}
};

