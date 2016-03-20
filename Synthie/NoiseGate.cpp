#include "stdafx.h"
#include "NoiseGate.h"
const double GATE_THRESHOLD = .001;

CNoiseGate::CNoiseGate()
{
}


CNoiseGate::~CNoiseGate()
{
}

void CNoiseGate::Process(double *frameIn, double *frameOut, double time)
{
	if (abs(frameIn[0]) < GATE_THRESHOLD && abs(frameIn[1]) < GATE_THRESHOLD){
		frameOut[0] = 0;
		frameOut[1] = 0;
	}
	else
	{
		frameOut[0] = frameIn[0];
		frameOut[1] = frameIn[1];
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
