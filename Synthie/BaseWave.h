
/**
* \file BaseWave.h
*
* \author Su Adanali
*
* \brief base class for waves and wav file player
*/

#pragma once
#include "AudioNode.h"
#include <vector>

class BaseWave : public CAudioNode
{
public:
	BaseWave();
	virtual ~BaseWave();

	///!Sets wavetables per wave
	virtual void SetWavetables() = 0;

	void SetFreq(double f) { mFreq = f; }
	//! Set the sine wave amplitude
	void SetAmplitude(double a) { mAmp = a; }

	double GetFreq() { return mFreq; }
	double GetAmp() { return mAmp; }
	double GetPhase() { return mPhase; }
	bool GetIfFilter() { return mFilter; }
	double GetWavetableSize() { return mWavetable.size(); }

protected:
	double mFreq;
	double mAmp;
	int mPhase;
	bool mFilter;
	std::vector<double> mWavetable;
};