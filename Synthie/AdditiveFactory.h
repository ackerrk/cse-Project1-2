#pragma once
#include "Additive.h"
class CAdditiveFactory
{
public:
	CAdditiveFactory();
	~CAdditiveFactory();

public:
	CAdditive *CAdditiveFactory::CreateInstrument();
	void CAdditiveFactory::SetNote(CNote *note);

private:
	vector<double> m_harmonics; //list of harmonics wanted to be added together
	vector<double> m_harm_amps;
	double m_vibrato;
	double m_vibrato_depth;
};

