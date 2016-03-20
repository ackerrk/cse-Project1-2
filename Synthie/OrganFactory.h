#pragma once
#include "Organ.h"
class COrganFactory
{
public:
	COrganFactory();
	~COrganFactory();

public:
	COrgan *COrganFactory::CreateInstrument();
	void COrganFactory::SetNote(CNote *note);

	void getDrawbar(int num);

private:
	vector<double> m_amps;
	vector<double> m_harmonics; //list of harmonics wanted to be added together
	double m_vibrato;
	double m_vibrato_depth;
};


