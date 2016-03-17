#pragma once
#include "Instrument.h"
#include "SineWave.h"
#include "TriangleWave.h"
#include "SquareWave.h"
#include "SawtoothWave.h"
#include <vector>
#include "AR.h"
#include "SubtractiveResonFilter.h"
#include "SubtractivePitchFilter.h"

//commit
//revert?
class CSubtractiveInstrument : public CInstrument
{
public:
	CSubtractiveInstrument();
	virtual ~CSubtractiveInstrument();
	virtual void Start() override;
	void SetNote(CNote* note);
	virtual bool Generate() override;
	//virtual void SetNote(CNote* note, double secPerBeat) override;

	void SetFreq(double f);
	void SetAmplitude(double a);
	void SetDuration(double d) { mDuration = d; }

	void ResonFilterSetup();

	enum Waveform { Sawtooth, Triangle, Square };

private:
	CSineWave mSinewave;
	CSawtoothWave mSawtooth;
	CTriangleWave mTriangle;
	CSquareWave mSquare;
	CSubtractiveResonFilter mReson;

	double mResonFrequency;
	double mResonBandwidth;

	double mDuration;
	double mTime;

	CSubtractiveResonFilter mSubtractiveReson;
	CSubtractivePitchFilter mSubtractivePitchFilter;

	CAR m_ar;

	Waveform mWaveform;

	void StringToWaveform(std::wstring waveform);

	bool mResonFilter;
	bool mFilterEnvelope;
	bool mADSREnvelope;
};
