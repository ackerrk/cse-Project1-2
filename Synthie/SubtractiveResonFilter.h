#pragma once
#include "SubtractiveFilters.h"
#include <vector>

class CSubtractiveResonFilter : public CSubtractiveFilters
{
public:
	CSubtractiveResonFilter();
	virtual ~CSubtractiveResonFilter();

	//! Start the node generation
	virtual void Start() override;

	//! Cause one sample to be generated
	virtual bool Generate() override;

	//! Set attack length
	void SetBandwidth(double bandwidth) { mBandwidth = bandwidth; }
	void SetFrequency(double frequency) { mFrequency = frequency; }

	struct FilterTerm
	{
		int m_delay;
		double m_weight;
	};

private:
	double mFrequency;
	double mBandwidth;
	double mGain;
	int mWrLoc;

	std::vector<double> mQueueX;
	std::vector<double> mQueueY;

	std::vector<FilterTerm> mFilterXTerms;
	std::vector<FilterTerm> mFilterYTerms;

	// Private methods
	void SetResonParameters();
};

