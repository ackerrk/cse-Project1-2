#include "stdafx.h"
#include "SubtractivePitchFilter.h"
#include "SubtractiveEnvelope.h"


CSubtractivePitchFilter::CSubtractivePitchFilter()
{
}


CSubtractivePitchFilter::~CSubtractivePitchFilter()
{
}

void CSubtractivePitchFilter::Start()
{
	mTime = 0;
	mPosition = 0;
	mSampleNum = 0;

	// Make sure you do this!
	mEnvelope->SetDuration(mDuration);
	mEnvelope->SetSampleRate(GetSampleRate());
	mEnvelope->Start();

	mSource->Start();
	auto valid = mSource->Generate();
	for (auto time = 0.; time < mDuration; time += GetSamplePeriod())
	{
		mQueueL.push_back(mSource->Frame(0));
		mQueueR.push_back(mSource->Frame(1));
		valid = mSource->Generate();
	}
}


bool CSubtractivePitchFilter::Generate()
{
	// No need to generate mEnvelope anymore!!
	mSampleNum = int(mPosition + 0.5) % mQueueL.size();

	m_frame[0] = mQueueL[mSampleNum];
	m_frame[1] = mQueueR[mSampleNum];

	mPosition += mEnvelope->GetEnvelopeLevel();

	if (mSampleNum < 0) mPosition = mQueueL.size();

	mTime += GetSamplePeriod();
	return mTime < mDuration;
}