#include "stdafx.h"
#include "AddSines.h"
#include <vector>
using namespace std;


CAddSines::CAddSines()
{
	m_amp = 1;
	m_vibrato = 0.;
	m_depth = 0.;
	m_vibrato_phase = 0.;
	m_time = 0;
}


CAddSines::~CAddSines()
{
}

void CAddSines::Start(){
	m_phase = 0;
}

bool CAddSines::Generate(){
	double samp = 0;
	double freq = 0;
	freq = m_freq - (m_depth * sin(2 * PI*m_vibrato*m_time));
	for (int i = 0; i < m_harmonics.size(); i++){
		double amplitude = m_amp / m_harmonics[i];

		//samp += amplitude*sin(m_phase*(m_harmonics[i]));
		samp += amplitude*sin(2 * PI*m_time*freq);
	}
	
	
	//m_vibrato_phase += (2 * PI * m_vibrato) * GetSamplePeriod();
	//m_phase += (2 * PI *(m_freq + m_depth * sin(m_vibrato_phase))) * GetSamplePeriod();
	//m_phase += 2 * PI * m_freq * GetSamplePeriod();
	m_frame[1] = m_frame[0] = samp;

	return true;
}
