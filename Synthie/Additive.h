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

private:
	CAR m_ar;
	double m_time;
	CAddSines m_sines;
};

