#pragma once
#include "Instrument.h"
#include <vector>

const int QUEUESIZE = 200000;
const double M_PI = 3.14159;
class CEffect :
	public CInstrument
{
public:
	virtual ~CEffect();

	void SetDelay(double delay) { m_delay = delay; }

	void SetWet(double wet) { m_wet = wet; }

	void SetDry(double dry) { m_dry = dry; }

	virtual void SetNote(CNote *note) override;

	virtual void Process(double *frameIn, double *frameOut, double time) = 0;

protected:
	CEffect();

	double	m_delay;
	double	m_wet;
	double	m_dry;
	int m_wrloc;
	int m_rdloc;
	double mTime = 5.0;
	std::vector<double> m_queue;
};

