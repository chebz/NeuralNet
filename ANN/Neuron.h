#pragma once
#include "stdafx.h"

class Neuron : public Poolable {
	std::vector<double> mWeights;

protected:
	const NeuronSettings &mSettings;

	virtual void reset() = 0;

	virtual void addNeuron(const Neuron* neuron, double weight) = 0;

	virtual void stepFunction() = 0;

	double getWeight(int iWeight) const;

	double mutate(double weight, double mutationRate);

public:
	Neuron(ObjectPool &pool, const NeuronSettings &settings);

	virtual ~Neuron() {}

	virtual void init(int numInputsPerNeuron);

	virtual void init(int numInputsPerNeuron, const Neuron *parent, double mutationRate);

	void update(const std::vector<Neuron*> &inputs);
};
