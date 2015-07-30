#pragma once
#include "stdafx.h"

class GeneticAlgorithm : public ObjectPool
{
	friend class Genome;

	const GeneticAlgorithmSettings mSettings;

	std::multiset<Genome*> mPopulation;

	double mTotalFitness;

	Genome *rouletteSelect();

	Genome *selectMate(Genome *pMateA);

	Genome *cross(const Genome &mum, const Genome &dad);

	Genome *cross(const Genome &parent);

public:
	GeneticAlgorithm(const GeneticAlgorithmSettings &settings);
	
	Genome *addGenome();

	void epoch();

	double getAverageFitness() const;

	double getBestFitness() const;

	double getWorstFitness() const;

	const std::multiset<Genome*> &getPopulation() const;
};

