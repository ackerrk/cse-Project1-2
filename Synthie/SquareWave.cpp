#include "stdafx.h"
#include "SquareWave.h"

using namespace std;

CSquareWave::CSquareWave()
{
	mPhase = 0;
	mAmp = 0.1;
	mFreq = 440;
}

CSquareWave::~CSquareWave()
{
}

void CSquareWave::Start()
{
	mPhase = 0;
	SetWavetables();
}

bool CSquareWave::Generate()
{
	m_frame[0] = mWavetable[mPhase];
	m_frame[1] = m_frame[0];

	mPhase = (mPhase + 1) % mWavetable.size();

	return true;
}

void CSquareWave::SetWavetables()
{
	auto tableSize = GetSampleRate();

	mWavetable.resize(tableSize);
	auto time = 0.;

	for (auto i = 0; i < tableSize; i++, time += 1. / GetSampleRate())
	{
		auto squareSample = 0.;
		int nyquist = GetSampleRate() / 2;
		auto harm = 1.;

		while (mFreq * harm < nyquist)
		{
			squareSample += mAmp / harm * sin(time * 2 * PI * mFreq * harm);
			harm += 2;
		}
		mWavetable[i] = squareSample;
	}
}