#pragma once
#include "Instrument.h"
#include "AR.h"
#include "OrganSines.h"
class COrgan :
	public CInstrument
{
public:
	COrgan();
	~COrgan();

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

	void SetHarmonics(int i, double h)
	{
		m_sines.AddHarmonic(i, h);
	}
	void SetVibrato(double vibrato, double depth){ m_sines.SetVibrato(vibrato); m_sines.SetVibratoDepth(depth); }

	void SetAmplitude(int i, double d) { m_sines.SetAmplitude(i, d); }

private:
	CAR m_ar;
	double m_time;
	COrganSines m_sines;
	double m_vibrato;
	double m_vibrato_depth;
};


