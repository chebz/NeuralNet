#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(const GeneticAlgorithmSettings &settings) :
	ObjectPool(settings.mGenomeFactory, settings.mMaxPopulation * 2), mSettings(settings) {
	for (int iGenome = 0; iGenome < settings.mMaxPopulation; iGenome++) {
		addGenome();
	}
}

Genome *GeneticAlgorithm::addGenome() {
	Genome *pGenome = dynamic_cast<Genome*>(getInstance());
	assert(pGenome != nullptr);
	mPopulation.insert(pGenome);
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

void GeneticAlgorithm::epoch() {
	while (mPopulation.size() < mPopulation.size() * 2) {
		auto pGenomeA = rouletteSelect();
		assert(pGenomeA);
		auto pGenomeB = selectMate(pGenomeA);
		assert(pGenomeB);

		if (UTILS.random01() < mSettings.mCrossoverRate) {
			mPopulation.insert(cross(*pGenomeA, *pGenomeB));
			mPopulation.insert(cross(*pGenomeB, *pGenomeA));
		}
		else {
			mPopulation.insert(cross(*pGenomeA));
			mPopulation.insert(cross(*pGenomeB));
		}
	}

	auto it = mPopulation.begin();

	while (it != mPopulation.end()) {
		if ((*it)->mIsParent) {
			(*it)->free();
			it = mPopulation.erase(it);
		}
		else {
			(*it)->mIsParent = true;
			++it;
		}
	}
}

Genome *GeneticAlgorithm::rouletteSelect() {
	double slice = Utils::getInstance().randomRange(0.0, mTotalFitness);
	double fitness = 0;
	int order = 0;

	for (auto pGenome : mPopulation) {
		fitness += pGenome->getFitness();

		if (fitness >= slice) {
			pGenome->mOrder = order++;
			return pGenome;
		}
	}
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

double GeneticAlgorithm::getBestFitness() const { return (*mPopulation.begin())->getFitness(); }

double GeneticAlgorithm::getWorstFitness() const { return (*mPopulation.rbegin())->getFitness(); }

const std::multiset<Genome*> &GeneticAlgorithm::getPopulation() const { return mPopulation; }