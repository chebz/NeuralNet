#pragma once
#include "stdafx.h"

class GenomeFactory : public PoolableFactory {
public:
	GenomeFactory() : PoolableFactory() {}

	virtual ~GenomeFactory() {}
};

