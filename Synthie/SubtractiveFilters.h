#pragma once
#include "AudioNode.h"

class CSubtractiveEnvelope;

class CSubtractiveFilters : public CAudioNode
{
public:
	CSubtractiveFilters();
	virtual ~CSubtractiveFilters();

	void SetEnvelope(CSubtractiveEnvelope* envelope) { mEnvelope = envelope; }

	//! Set the source audio
	void SetSource(CAudioNode* source) { mSource = source; }
	void SetDuration(double duration) { mDuration = duration; }

protected:
	CAudioNode* mSource;
	CSubtractiveEnvelope* mEnvelope;

	double mDuration;
	double mTime;
};

