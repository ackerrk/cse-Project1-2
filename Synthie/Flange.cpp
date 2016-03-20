#include "stdafx.h"
#include "Flange.h"

const double MAXDELAY = 2.5;
const double MINDELAY = 0.5;

CFlange::CFlange()
{
	m_count = 0;
}


CFlange::~CFlange()
{
}

void CFlange::Process(double *frameIn, double *frameOut, double time)
{
	m_queue[m_wrloc] = frameIn[0];
	m_queue[m_wrloc + 1] = frameIn[1];

	double flange = (MAXDELAY - MINDELAY) * abs(sin(M_PI * abs(time))) + MINDELAY;
	
	frameOut[0] = m_dry * frameIn[0] + m_wet * m_queue[(m_rdloc) % QUEUESIZE];
	frameOut[1] = m_dry * frameIn[1] + m_wet * m_queue[(m_rdloc + 1) % QUEUESIZE];

	//double flange = 0.006 + sin(0.25 * 2 * M_PI * time) * 0.004;

	int delay = int((flange*GetSampleRate()));

	m_wrloc = (m_wrloc + 2) % QUEUESIZE;
	m_rdloc = (m_wrloc + QUEUESIZE - delay) % QUEUESIZE;
}

void CFlange::Start()
{
	m_wrloc = 0;
	m_rdloc = 0;
}

bool CFlange::Generate()
{
	return true;
}