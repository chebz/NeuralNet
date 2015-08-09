#pragma once
#include "stdafx.h"

struct NeuronSettings;

class Neuron : public Poolable {
	double mValue;

	double mBiasWeight;

	std::vector<double> mWeights;

protected:
	const NeuronSettings &mSettings;

	virtual void addN(const Neuron* N, double weight);

	virtual void stepFunction();

	double getWeight(int iWeight) const;

	double mutate(double weight, double mutationRate);

public:
	Neuron(ObjectPool &pool, const NeuronSettings &settings);

	virtual ~Neuron() {}

	virtual void init(int numInputsPerNeuron);

	virtual void init(int numInputsPerNeuron, const Neuron *parent, double mutationRate);

	void update(const std::vector<Neuron*> &inputs);

	double getValue() const { return mValue; }
};
