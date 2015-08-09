#pragma once
#include "stdafx.h"

class Neuron;
struct NeuronLayerSettings;

class NeuronLayer : public Poolable, public ObjectPool {
	const NeuronLayerSettings &mSettings;

	std::vector<Neuron*> mpNeurons;

	Neuron &addNeuron();

	Neuron *getNeuron(int iNeuron) const;

	int NMutation() const { return 0; } //TODO

public:
	NeuronLayer(ObjectPool &pool, const NeuronLayerSettings &settings);

	~NeuronLayer();

	int init(int numInputsPerNeuroneuron);

	int init(int numInputsPerNeuroneuron, int numNeurons);

	int init(int numInputsPerNeuron, const NeuronLayer *parent, double mutationRate);

	int init(int numInputsPerNeuron, const NeuronLayer *mum, const NeuronLayer *dad, double mutationRate);

	int init(int numInputsPerNeuron, int numNeurons, const NeuronLayer &mum, const NeuronLayer &dad, double mutationRate);

	void update(const std::vector<double> &inputs);

	const std::vector<double> getOutputs() const;

	void free();
};