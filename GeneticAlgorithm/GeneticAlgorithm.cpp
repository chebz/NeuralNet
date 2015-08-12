#include "GeneticAlgorithm.h"
#include <algorithm> 

GeneticAlgorithm::GeneticAlgorithm(const GeneticAlgorithmSettings &settings) :
ObjectPool(settings.mGenomeFactory, settings.mMaxPopulation * 2), mSettings(settings), sorted(false) {
	for (int iGenome = 0; iGenome < settings.mMaxPopulation; iGenome++) {
		addGenome()->init();
	}
}

Genome *GeneticAlgorithm::addGenome() {
	Genome *pGenome = dynamic_cast<Genome*>(getInstance());
	assert(pGenome != nullptr);
	mPopulation.push_back(pGenome);
	return pGenome;
}

Genome *GeneticAlgorithm::cross(const Genome &mum, const Genome &dad) {
	auto pBaby = dynamic_cast<Genome*>(getInstance());
	assert(pBaby != nullptr);
	pBaby->init(mum, dad, mSettings.mMutationRate);
	return pBaby;
}

Genome *GeneticAlgorithm::cross(const Genome &parent) {
	auto pBaby = dynamic_cast<Genome*>(getInstance());
	assert(pBaby != nullptr);
	pBaby->init(parent, mSettings.mMutationRate);
	return pBaby;
}

bool genomeComp(const Genome *lhs, const Genome *rhs) {
	return (lhs->getFitness() > rhs->getFitness());
}

void GeneticAlgorithm::sort() {
	if (sorted)
		return;
	std::sort(mPopulation.begin(), mPopulation.end(), genomeComp);
}

void GeneticAlgorithm::epoch() {
	sort();

	while (mPopulation.size() < mSettings.mMaxPopulation * 2) {
		auto pGenomeA = rouletteSelect();
		assert(pGenomeA);
		auto pGenomeB = selectMate(pGenomeA);
		assert(pGenomeB);

		if (UTILS.random01() < mSettings.mCrossoverRate) {
			mPopulation.push_back(cross(*pGenomeA, *pGenomeB));
			mPopulation.push_back(cross(*pGenomeB, *pGenomeA));
		}
		else {
			mPopulation.push_back(cross(*pGenomeA));
			mPopulation.push_back(cross(*pGenomeB));
		}
	}

	auto it = mPopulation.begin();

	for (int iGenome = 0; iGenome < mSettings.mMaxPopulation; iGenome++) {
		(*it)->free();
		it = mPopulation.erase(it);
	}
}

Genome *GeneticAlgorithm::rouletteSelect() {
	double slice = Utils::getInstance().randomRange(0.0, mTotalFitness);
	slice = Utils::getInstance().randomRange(0.0, slice);

	double fitness = 0;
	int order = 0;

	for (int iGenome = 0; iGenome < mSettings.mMaxPopulation; iGenome++) {
		auto pGenome = mPopulation[iGenome];
		pGenome->mOrder = order++;
		fitness += pGenome->getFitness();

		if (fitness >= slice) {
			return pGenome;
		}
	}

	assert(false);

	return nullptr;
}

Genome *GeneticAlgorithm::selectMate(Genome *pMateA) {
	if (mPopulation.size() == 1)
		return nullptr;

	int orderMin = std::max((int)0, pMateA->mOrder - mSettings.mMateThreshold);
	int orderMax = std::min(pMateA->mOrder + mSettings.mMateThreshold, static_cast<int>(mPopulation.size()));
	int iMateB = Utils::getInstance().randomRangeExcept(orderMin, orderMax, pMateA->mOrder);
	auto it = mPopulation.begin();
	std::advance(it, iMateB);
	auto pMateB = *it;
	pMateB->mOrder = iMateB;
	return pMateB;
}

double GeneticAlgorithm::getAverageFitness() const { return mTotalFitness / mPopulation.size(); }

double GeneticAlgorithm::getBestFitness() {
	sort();
	return (*mPopulation.begin())->getFitness();
}

double GeneticAlgorithm::getWorstFitness() {
	sort();
	return (*mPopulation.rbegin())->getFitness();
}

const std::vector<Genome*> &GeneticAlgorithm::getPopulation() const { return mPopulation; }

const std::vector<Genome*> &GeneticAlgorithm::getSortedPopulation() { 
	sort(); 
	return mPopulation;
}