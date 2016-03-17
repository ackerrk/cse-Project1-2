#pragma once
#include "AudioNode.h"

//thought each wave would need an ADSR envelope, but I was wrong
class CSubtractiveEnvelope : public CAudioNode
{
public:
	CSubtractiveEnvelope();
	virtual ~CSubtractiveEnvelope();

	virtual void Start() override {};

	virtual bool Generate() override { return false; }
	
	void SetDuration(double duration) { mDuration = duration; }

	double GetEnvelopeLevel() { return mEnvelopeLevel; }

protected:
	double mEnvelopeLevel;
	double mDuration;
	double mTime;
};

