#pragma once
#include "OddSinesInstrument.h"
class COddSinesFactory
{
public:
	COddSinesFactory();
	~COddSinesFactory();

	COddSinesInstrument *COddSinesFactory::CreateInstrument();
	void COddSinesFactory::SetNote(CNote *note);

private:
	double m_amps[4];
};

