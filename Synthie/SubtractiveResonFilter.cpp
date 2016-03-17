#include "stdafx.h"
#include "SubtractiveResonFilter.h"
#include "SubtractiveEnvelope.h"


CSubtractiveResonFilter::CSubtractiveResonFilter()
{
	mBandwidth = 0.01;
	mFrequency = 0.02;
	mGain = 10;
}


CSubtractiveResonFilter::~CSubtractiveResonFilter()
{
}

void CSubtractiveResonFilter::Start()
{
	mTime = 0;
	mWrLoc = 0;

	auto queueSize = int(2 * GetSampleRate());
	mQueueX.resize(queueSize);
	mQueueY.resize(queueSize);
	SetResonParameters();

	// Make sure you do this!!
	mEnvelope->SetDuration(mDuration);
	mEnvelope->SetSampleRate(GetSampleRate());
	mEnvelope->Start();
}

bool CSubtractiveResonFilter::Generate()
{
	// No need to generate mEnvelope anymore!!
	double audio[2];

	auto queueSize = int(2 * GetSampleRate());

	audio[0] = mSource->Frame(0);
	audio[1] = mSource->Frame(1);

	mWrLoc = (mWrLoc + 2) % queueSize;
	mQueueX[mWrLoc] = audio[0];
	mQueueX[mWrLoc + 1] = audio[1];

	audio[0] = 0;
	audio[1] = 0;

	for (auto xTerm : mFilterXTerms)
	{
		auto delayLength = xTerm.m_delay * 2;
		auto rdloc = (mWrLoc + queueSize - delayLength) % queueSize;

		audio[0] = audio[0] + mQueueX[rdloc] * xTerm.m_weight;
		rdloc = (rdloc + 1) % queueSize;

		audio[1] = audio[1] + mQueueX[rdloc] * xTerm.m_weight;
	}

	for (auto yTerm : mFilterYTerms)
	{
		auto delayLength = yTerm.m_delay * 2;
		auto rdloc = (mWrLoc + queueSize - delayLength) % queueSize;

		audio[0] = audio[0] + mQueueY[rdloc] * yTerm.m_weight;
		rdloc = (rdloc + 1) % queueSize;

		audio[1] = audio[1] + mQueueY[rdloc] * yTerm.m_weight;
	}

	mQueueY[mWrLoc] = audio[0];
	mQueueY[mWrLoc + 1] = audio[1];
	
	// get envelope level for wet vs dry
	auto wetLevel = mEnvelope->GetEnvelopeLevel();
	auto dryLevel = 1 - wetLevel;

	m_frame[0] = wetLevel * audio[0] + dryLevel * mSource->Frame(0);
	m_frame[1] = wetLevel * audio[1] + dryLevel * mSource->Frame(1);

	// Update time
	mTime += GetSamplePeriod();
	// We return true until the time reaches the duration.
	return mTime < mDuration;
}


void CSubtractiveResonFilter::SetResonParameters()
{
	auto R = 1. - mBandwidth / 2.;
	auto costheta = (2. * R * cos(2 * PI * mFrequency)) / (1. + pow(R, 2.));
	auto sintheta = sqrt(1. - pow(costheta, 2.));
	auto A = (1. - pow(R, 2.)) * sintheta;

	A = A * mGain;

	mFilterXTerms.clear();
	mFilterYTerms.clear();

	FilterTerm term;
	term.m_delay = 0;
	term.m_weight = A;

	mFilterXTerms.push_back(term);

	term.m_delay = 1;
	term.m_weight = 2 * R * costheta;
	mFilterYTerms.push_back(term);

	term.m_delay = 2;
	term.m_weight = -pow(R, 2);
	mFilterYTerms.push_back(term);
}
