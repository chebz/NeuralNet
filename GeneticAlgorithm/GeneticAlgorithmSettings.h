#pragma once
struct GenomeSettings {
	GenomeSettings() {}
	virtual ~GenomeSettings() {}
};

struct GeneticAlgorithmSettings {
	double mMutationRate;
	double mCrossoverRate;
	int mMateThreshold;
	int mMaxPopulation;

	const GenomeFactory &mGenomeFactory;

	GeneticAlgorithmSettings(const GenomeFactory &genomeFactory) :
		mMutationRate(0.1),
		mCrossoverRate(0.7),
		mMateThreshold(5),
		mGenomeFactory(genomeFactory) {}
};

