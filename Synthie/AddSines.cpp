#include "stdafx.h"
#include "AddSines.h"


CAddSines::CAddSines()
{
	m_amp = 1;
}


CAddSines::~CAddSines()
{
}

void CAddSines::Start(){
	m_phase = 0;
}

bool CAddSines::Generate(){
	double samp = 0;
	for (int i = 0; i < m_harmonics.size(); i++){
		double amplitude = m_amp / m_harmonics[i];

		samp += amplitude*sin(m_phase*(m_harmonics[i]));
	}
	m_frame[1] = m_frame[0] = samp;
	m_phase += 2 * PI * m_freq * GetSamplePeriod();

	return true;
}