#pragma once
#include <functional>
#include "stdafx.h"
#include "NeuronFactory.h"
#include "NeuronLayerFactory.h"
#include "NeuronNetFactory.h"

struct NeuronSettings {
	double mWeightPerturbation;
	double mBias;
	double mActivationResponse;

	const NeuronFactory mFactory;

	NeuronSettings();
};

struct NeuronLayerSettings {
	UINT mNumNeuronsPerLayerMin;
	UINT mNumNeuronsPerLayerMax;
	UINT mNumNeuronsPertrubation;

	const NeuronLayerFactory mFactory;

	const NeuronSettings &mNSettings;

	NeuronLayerSettings(const NeuronSettings &nSettings);
};

struct NeuronNetSettings : GenomeSettings {
	UINT mNumInputs;
	UINT mNumOutputs;
	
	UINT mNumLayersMin;
	UINT mNumLayersMax;
	UINT mNumLayersPertrubation;

	const NeuronNetFactory mFactory;

	const NeuronLayerSettings &mLayerSettings;

	NeuronNetSettings(const NeuronLayerSettings &layerSettings);
};

