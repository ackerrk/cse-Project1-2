#include "stdafx.h"
#include "SawtoothWave.h"

using namespace std;

CSawtoothWave::CSawtoothWave()
{
	mPhase = 0;
	mAmp = 0.1;
	mFreq = 440;
}

CSawtoothWave::~CSawtoothWave()
{
}

void CSawtoothWave::Start()
{
	mPhase = 0;
	SetWavetables();
}

bool CSawtoothWave::Generate()
{
	m_frame[0] = mWavetable[mPhase];
	m_frame[1] = m_frame[0];

	mPhase = (mPhase + 1) % mWavetable.size();

	return true;
}

void CSawtoothWave::SetWavetables()
{
	auto tableSize = GetSampleRate();

	mWavetable.resize(tableSize);
	auto time = 0.;

	for (auto i = 0; i < tableSize; i++, time += 1. / GetSampleRate())
	{
		auto sawtoothSample = 0.;
		int nyquist = GetSampleRate() / 2;
		auto harm = 1.;

		while (mFreq * harm < nyquist)
		{
			sawtoothSample += mAmp / harm * sin(time * 2 * PI * mFreq * harm);
			harm += 1;
		}
		mWavetable[i] = sawtoothSample;
	}
}