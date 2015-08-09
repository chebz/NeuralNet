#pragma once
#include "stdafx.h"

struct GenomeSettings;

class GenomeFactory : public PoolableFactory {
protected:
	const GenomeSettings &mSettings;

public:
	GenomeFactory(const GenomeSettings &settings) :
		PoolableFactory(),
		mSettings(settings)	{}

	virtual ~GenomeFactory() {}
};

