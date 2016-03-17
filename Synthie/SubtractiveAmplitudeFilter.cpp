#include "stdafx.h"
#include "SubtractiveAmplitudeFilter.h"
#include "SubtractiveEnvelope.h"


CSubtractiveAmplitudeFilter::CSubtractiveAmplitudeFilter()
{
}


CSubtractiveAmplitudeFilter::~CSubtractiveAmplitudeFilter()
{
}

void CSubtractiveAmplitudeFilter::Start()
{
	mTime = 0;
	mEnvelope->SetDuration(mDuration);
	mEnvelope->SetSampleRate(GetSampleRate());
	mEnvelope->Start();
}


bool CSubtractiveAmplitudeFilter::Generate()
{
	auto amplitudeFactor = mEnvelope->GetEnvelopeLevel();

	m_frame[0] = amplitudeFactor * mSource->Frame(0);
	m_frame[1] = amplitudeFactor * mSource->Frame(1);

	mTime += GetSamplePeriod();
	return mTime < mDuration;
}
