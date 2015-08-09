#pragma once
#include "stdafx.h"

class Neuron;
class NeuronLayer;
struct NeuronNetSettings;

class NeuronNet : public Genome, public ObjectPool {

	std::vector<NeuronLayer*> mpLayers;

	NeuronLayer *mpOutputLayer;

	NeuronLayer &addLayer();

	NeuronLayer *getLayer(int iLayer) const;

	int layerMutation() const { return 0; } //TODO

public:
	NeuronNet(ObjectPool &pool, const NeuronNetSettings &settings);

	~NeuronNet();

	void init();

	void init(const Genome &parent, double mutationRate);

	void init(const Genome &mum, const Genome &dad, double mutationRate);

	void update(const std::vector<double> inputs);

	const std::vector<double> getOutputs() const;

	void free();
};

