#pragma once
#include "Instrument.h"
#include "AR.h"
#include "AddSines.h"

class CAdditive :
	public CInstrument
{
public:
	CAdditive();
	~CAdditive();

	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote* note);

	void SetDuration(double d)
	{
		m_ar.SetDuration(d);
	}

	void SetFreq(double f)
	{
		m_sines.SetFreq(f);
	}

	void SetHarmonics(int size, int i, double h)
	{
		m_sines.AddHarmonic(size, i, h);
	}
	void SetAmps(int size, int i, double a){
		m_sines.AddAmp(size, i, a);
	}
	void SetVibrato(double vibrato, double depth){ m_sines.SetVibrato(vibrato); m_sines.SetVibratoDepth(depth); }

private:
	CAR m_ar;
	double m_time;
	CAddSines m_sines;
	double m_vibrato;
	double m_vibrato_depth;
	bool m_crossfading;
	double m_next_freq;
};

