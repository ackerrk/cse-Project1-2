#pragma once
#include "SubtractiveFilters.h"

class CSubtractiveAmplitudeFilter : public CSubtractiveFilters
{
public:
	CSubtractiveAmplitudeFilter();
	virtual ~CSubtractiveAmplitudeFilter();

	//! Start the node generation
	virtual void Start() override;

	//! Cause one sample to be generated
	virtual bool Generate() override;
};

