#pragma once
#include "SubtractiveEnvelope.h"

class CSubtractiveADSREnvelope : public CSubtractiveEnvelope
{
public:
	CSubtractiveADSREnvelope();
	virtual ~CSubtractiveADSREnvelope();

	//! Start the node generation
	virtual void Start() override;

	//! Cause one sample to be generated
	virtual bool Generate() override;

	//! Set attack length
	void SetAttack(double attack) { mAttack = attack; }
	//! Set Decay length
	void SetDecay(double decay) { mDecay = decay; }
	//! Set Sustain level
	void SetSustainLevel(double susLevel) { mSustainLevel = susLevel; }
	//! Set Release length
	void SetRelease(double release) { mRelease = release; }

private:
	double mAttack;
	double mDecay;
	double mSustainLevel;
	double mRelease;
};

