#pragma once
#include "stdafx.h"

struct NeuronDoubleSettings : NeuronSettings {
	double mBias;

	NeuronDoubleSettings() : NeuronSettings(), mBias(-1) {}
};

class NeuronDouble : public Neuron
{
	double mValue;

	double mBiasWeight;

protected:
	void reset();

	void addNeuron(const Neuron* neuron, double weight);

	void stepFunction();

public:
	NeuronDouble(ObjectPool &pool, const NeuronDoubleSettings &settings) :
		Neuron(pool, settings), mValue(0) {}

	virtual void init(int numInputsPerNeuron);

	virtual void init(int numInputsPerNeuron, const Neuron *parent, double mutationRate);

	void cross(Neuron *pOther);

	void mutate(double mutationRate, double maxPerturbation);

	void setValue(double value) { mValue = value; }

	double getValue() const { return mValue; }
};