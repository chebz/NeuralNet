#pragma once
#include "stdafx.h"

class NeuralNet : public Genome, public ObjectPool {
	const NeuralNetSettings mSettings;

	std::vector<NeuronLayer*> mLayers;

	NeuronLayer *mpOutputLayer;

	NeuronLayer &addLayer();

	NeuronLayer *getLayer(int iLayer) const;

	int layerMutation() const { return 0; } //TODO

public:
	NeuralNet(ObjectPool &pool, const NeuralNetSettings &settings);

	~NeuralNet();

	void init();

	void init(const Genome &parent, double mutationRate);

	void init(const Genome &mum, const Genome &dad, double mutationRate);

	void update(const std::vector<Neuron*> &inputs);

	const std::vector<Neuron*> &getOutputs() const { return mLayers[mLayers.size() - 1]->getNeurons(); }

	void cross(const Genome &otherParent, Genome &baby, double crossoverRate);

	void mutate(double mutationRate);
};

