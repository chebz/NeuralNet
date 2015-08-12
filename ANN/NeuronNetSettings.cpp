#include "NeuronNetSettings.h"

NeuronSettings::NeuronSettings() :
	mWeightPerturbation(0.3),
	mBias(-1),
	mActivationResponse(0.2),
	mFactory(*this) {}

NeuronLayerSettings::NeuronLayerSettings(const NeuronSettings &NSettings) :
	mNumNeuronsPerLayerMin(1),
	mNumNeuronsPerLayerMax(1),
	mNumNeuronsPertrubation(0),
	mNSettings(NSettings),
	mFactory(*this) {}

NeuronNetSettings::NeuronNetSettings(const NeuronLayerSettings &layerSettings) :
	mNumInputs(1),
	mNumOutputs(1),
	mNumLayersMin(1),
	mNumLayersMax(1),
	mNumLayersPertrubation(0),
	mLayerSettings(layerSettings),
	mFactory(*this) {}