#pragma once
#include "Neuron.h"
#include "NeuronFactory.h"
#include "NeuronFactoryDouble.h"

class NeuronFactory;
class NeuronFactoryDouble;

struct NeuronDoubleSettings : NeuronSettings {
private:
	const NeuronFactoryDouble mFactory;

public:
	double mBias;

	NeuronDoubleSettings() :
		NeuronSettings(),
		mBias(-1),
		mFactory((NeuronFactoryDouble(this))) {}

	const NeuronFactory &getNeuronFactory() const {
		return mFactory;
	}
};

class NeuronDouble : public Neuron {
	double mValue;

	double mBiasWeight;

protected:
	void addNeuron(const Neuron* neuron, double weight);

	void stepFunction();

public:
	NeuronDouble(ObjectPool &pool, const NeuronDoubleSettings &settings) :
		Neuron(pool, settings), mValue(0) {}

	virtual void init(int numInputsPerNeuron);

	virtual void init(int numInputsPerNeuron, const Neuron *parent, double mutationRate);

	void setValue(double value) { mValue = value; }

	double getValue() const { return mValue; }
};