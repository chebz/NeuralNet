#pragma once
struct GeneticAlgorithmSettings {
	double mMutationRate;
	double mCrossoverRate;
	int mMateThreshold;
	int mMaxPopulation;

	GenomeFactory &mGenomeFactory;

	GeneticAlgorithmSettings(GenomeFactory &genomeFactory) :
		mMutationRate(0.1),
		mCrossoverRate(0.7),
		mMateThreshold(5),
		mGenomeFactory(genomeFactory) {}
};

