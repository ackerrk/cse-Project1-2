#pragma once
#include "SubtractiveInstrument.h"


class CSubtractiveInstrumentFactory
{
public:
	CSubtractiveInstrumentFactory();
	~CSubtractiveInstrumentFactory();

public:
	CSubtractiveInstrumentFactory *CSubtractiveInstrumentFactory::CreateInstrument();
	void CSubtractiveInstrumentFactory::SetNote(CNote *note);

private:
	vector<double> m_harmonics; //list of harmonics wanted to be added together
};

