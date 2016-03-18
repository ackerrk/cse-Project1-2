#include "stdafx.h"
#include "Reverb.h"
#include <cmath>
const double g = .001;
CReverb::CReverb()
{
}


CReverb::~CReverb()
{
}

void CReverb::Process(double *frameIn, double *frameOut, double time)
{

	

	frameOut[0] = m_dry * frameIn[0] + m_wet * m_queue[m_rdloc];
	frameOut[1] = m_dry * frameIn[1] + m_wet * m_queue[m_rdloc + 1];

	m_queue[m_wrloc] = frameIn[0] + frameOut[0] * pow(g, time);
	m_queue[m_wrloc + 1] = frameIn[1] + frameOut[1] * pow(g, time);
	
	m_wrloc = (m_wrloc + 2) % QUEUESIZE;
	m_rdloc = (m_rdloc + 2) % QUEUESIZE;

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