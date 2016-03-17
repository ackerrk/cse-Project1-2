#include "stdafx.h"
#include "TriangleWave.h"
#include <cmath>

using namespace std;

CTriangleWave::CTriangleWave()
{
	mPhase = 0;
	mAmp = 0.1;
	mFreq = 440;
}

CTriangleWave::~CTriangleWave()
{
}

void CTriangleWave::Start()
{
	mPhase = 0;
	SetWavetables();
}

bool CTriangleWave::Generate()
{
	m_frame[0] = mWavetable[mPhase];
	m_frame[1] = m_frame[0];

	mPhase = (mPhase + 1) % mWavetable.size();

	return true;
}

void CTriangleWave::SetWavetables()
{
	auto tableSize = GetSampleRate();

	mWavetable.resize(tableSize);
	auto time = 0.;
	auto count = 0;
	for (auto i = 0; i < tableSize; i++, time += 1. / GetSampleRate())
	{
		auto triangleSample = 0.;
		int nyquist = GetSampleRate() / 2;
		auto harm = 1.;

		while (mFreq * harm < nyquist)
		{
			triangleSample += pow(-1, count) * mAmp / pow(harm, 2)
				* sin(time * 2 * PI * mFreq * harm);
			harm += 2;
			count++;
		}
		mWavetable[i] = triangleSample;
	}
}