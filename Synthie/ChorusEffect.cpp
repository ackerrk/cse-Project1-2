#include "stdafx.h"
#include "ChorusEffect.h"
#include <cmath>


CChorusEffect::CChorusEffect()
{
}


CChorusEffect::~CChorusEffect()
{
}

void CChorusEffect::Process(double* frameIn, double* frameOut, double time)
{	
	m_queue[m_wrloc] = frameIn[0];
	m_queue[m_wrloc + 1] = frameIn[1];

	frameOut[0] = m_dry * frameIn[0] + m_wet * m_queue[(m_rdloc) % QUEUESIZE];
	frameOut[1] = m_dry * frameIn[1] + m_wet * m_queue[(m_rdloc + 1) % QUEUESIZE];

	double length = 0.025 + sin(0.25 * 2 * M_PI * time) * 0.004;

	int delay = int((length * GetSampleRate()));

	m_wrloc = (m_wrloc + 2) % QUEUESIZE;
	m_rdloc = (m_wrloc + QUEUESIZE - delay) % QUEUESIZE;
}

void CChorusEffect::Start()
{
	m_wrloc = 0;
	m_rdloc = 0;
}

bool CChorusEffect::Generate()
{
	return true;
}
