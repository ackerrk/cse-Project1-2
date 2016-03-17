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
};

