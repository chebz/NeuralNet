#pragma once
#include "stdafx.h"

class NeuronLayer : public Poolable, public ObjectPool {
	const NeuronLayerSettings &mSettings;

	std::vector<Neuron*> mNeurons;

	Neuron &addNeuron();

	Neuron *getNeuron(int iNeuron) const;

	int neuronMutation() const { return 0; } //TODO

public:
	NeuronLayer(ObjectPool &pool, const NeuronLayerSettings &settings);

	~NeuronLayer();

	int init(int numInputsPerNeuron);

	int init(int numInputsPerNeuron, int numNeurons);

	int init(int numInputsPerNeuron, const NeuronLayer *parent, double mutationRate);

	int init(int numInputsPerNeuron, const NeuronLayer *mum, const NeuronLayer *dad, double mutationRate);

	int init(int numInputsPerNeuron, int numNeurons, const NeuronLayer &mum, const NeuronLayer &dad, double mutationRate);

	void update(const std::vector<Neuron*> &inputs);

	const std::vector<Neuron*> &getNeurons() const { return mNeurons; }
};