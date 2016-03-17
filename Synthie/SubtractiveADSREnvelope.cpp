#include "stdafx.h"
#include "SubtractiveADSREnvelope.h"


CSubtractiveADSREnvelope::CSubtractiveADSREnvelope()
{
	mAttack = 0.05;
	mDecay = 0.;
	mSustainLevel = 1.;
	mRelease = 0.05;
}


CSubtractiveADSREnvelope::~CSubtractiveADSREnvelope()
{
}

void CSubtractiveADSREnvelope::Start()
{
	mEnvelopeLevel = 1.;
	mTime = 0.;
}

bool CSubtractiveADSREnvelope::Generate()
{
	if (mTime <= mAttack) // attack
	{
		mEnvelopeLevel = mTime / mAttack * mSustainLevel;
	}
	else if (mTime > mDuration - mRelease) // release
	{
		mEnvelopeLevel = (1 - (mTime - (mDuration - mRelease)) / mRelease) * mSustainLevel;
	}
	else if (mTime > mAttack && mTime <= mAttack + mDecay) // decay
	{
		mEnvelopeLevel = (mSustainLevel - 1) * ((mTime - (mDuration - mDecay)) / mDecay) + 1;
	}
	else // sustain
	{
		mEnvelopeLevel = mSustainLevel;
	}

	mTime += GetSamplePeriod();
	return mTime < mDuration;
}
