#include "Genome.h"

void Genome::init() {
	mIsParent = true;
}

void Genome::init(const Genome &parent, double mutationRate) {
	mIsParent = false;
}

void Genome::init(const Genome &mum, const Genome &dad, double mutationRate) {
	mIsParent = false;
}

void Genome::setFitness(double fitness) {
	auto ga = dynamic_cast<GeneticAlgorithm&>(getPool());
	ga.mTotalFitness -= mFitness;
	ga.mTotalFitness += fitness;
	mFitness = fitness;
}