#pragma once
#include "stdafx.h"

struct GenomeSettings;

class Genome : public Poolable {
	friend class GeneticAlgorithm;

private:
	int mOrder;
	bool mIsParent;

protected:
	const GenomeSettings &mSettings;

	double mFitness;

	Genome(ObjectPool &pool, const GenomeSettings &settings);

public:
	virtual ~Genome() = 0;

	virtual void init();

	virtual void init(const Genome &parent, double mutationRate);

	virtual void init(const Genome &mum, const Genome &dad, double mutationRate);

	friend bool operator < (const Genome& lhs, const Genome& rhs) {
		return (lhs.mFitness < rhs.mFitness);
	}

	void setFitness(double fitness);

	double getFitness() const { return mFitness; }
};