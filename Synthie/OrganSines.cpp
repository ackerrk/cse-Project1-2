#include "stdafx.h"
#include "OrganSines.h"
#include <vector>
using namespace std;


COrganSines::COrganSines()
{
	m_vibrato = 0.;
	m_depth = 0.;
	m_vibrato_phase = 0.;
	m_time = 0;
}


COrganSines::~COrganSines()
{
}

void COrganSines::Start(){
	m_phase = 0;
}

bool COrganSines::Generate(){
	double samp = 0;
	double freq = 0;
	freq = m_freq - (m_depth * sin(2 * PI*m_vibrato*m_time));
	for (int i = 0; i < 9; i++){
		//double amplitude = m_amps[i] / m_harmonics[i];

		//samp += m_amps[i]*sin(m_phase*(m_harmonics[i]));
		samp += m_amps[i]*sin(2 * PI*m_time*freq*m_harmonics[i]);
	}


	//m_vibrato_phase += (2 * PI * m_vibrato) * GetSamplePeriod();
	//m_phase += (2 * PI *(m_freq + m_depth * sin(m_vibrato_phase))) * GetSamplePeriod();
	//m_phase += 2 * PI * m_freq * GetSamplePeriod();
	m_frame[1] = m_frame[0] = samp;

	return true;
}
