#include "stdafx.h"
#include "NoiseGate.h"
const double GATE_THRESHOLD = 0.4;

CNoiseGate::CNoiseGate()
{
}


CNoiseGate::~CNoiseGate()
{
}

void CNoiseGate::Process(double *frameIn, double *frameOut, double time)
{
	if (frameIn[0] < GATE_THRESHOLD && frameIn[1] < GATE_THRESHOLD){
		frameOut[0] = frameOut[1] = 0;
	}
}

void CNoiseGate::Start()
{
	m_wrloc = 0;
	m_rdloc = 0;
}

bool CNoiseGate::Generate()
{
	return true;
}
