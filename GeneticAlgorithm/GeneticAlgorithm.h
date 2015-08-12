#pragma once
#include "stdafx.h"

class GeneticAlgorithm : public ObjectPool
{
	friend class Genome;

	const GeneticAlgorithmSettings mSettings;

	std::vector<Genome*> mPopulation;

	double mTotalFitness;

	bool sorted;

	Genome *rouletteSelect();

	Genome *selectMate(Genome *pMateA);

	Genome *cross(const Genome &mum, const Genome &dad);

	Genome *cross(const Genome &parent);

	void sort();

public:
	GeneticAlgorithm(const GeneticAlgorithmSettings &settings);
	
	Genome *addGenome();

	void epoch();

	double getAverageFitness() const;

	double getBestFitness();

	double getWorstFitness();

	const std::vector<Genome*> &getPopulation() const;

	const std::vector<Genome*> &getSortedPopulation();
};

