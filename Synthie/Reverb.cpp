#include "stdafx.h"
#include "Reverb.h"
#include <cmath>
const double g = .001;
CReverb::CReverb()
{
	m_reverb[0] = 0;
	m_reverb[1] = 0;
}


CReverb::~CReverb()
{
}

void CReverb::Process(double *frameIn, double *frameOut, double time)
{
	m_queue[m_wrloc] = frameIn[0];
	m_queue[m_wrloc + 1] = frameIn[1];

	int delay = int((.5 * GetSampleRate() ));

	
	frameOut[0] = m_dry * frameIn[0] + m_wet * m_queue[(m_rdloc) % QUEUESIZE]*.5;
	frameOut[1] = m_dry * frameIn[1] + m_wet * m_queue[(m_rdloc + 1) % QUEUESIZE]*.5;

	m_wrloc = (m_wrloc + 2) % QUEUESIZE;
	m_rdloc = (m_wrloc + QUEUESIZE - delay) % QUEUESIZE;
}

void CReverb::Start()
{
	m_wrloc = 0;
	m_rdloc = 0;
}

bool CReverb::Generate()
{
	return true;
}