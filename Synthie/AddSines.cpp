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
	m_fadein = 0;
	m_fadeout = 0;
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
			samp += m_harm_amps[i]*sin(2 * PI*m_time*freq*m_harmonics[i]);	
	}

	//if (m_crossfading == true){ samp = CrossFade(samp); }
	double ramp;
	if (m_fadein != 0 && m_time <= m_fadein){
		ramp = m_time / m_fadein;
	}
	else if ( (m_fadeout!=0) && (m_duration - m_time)<= m_fadeout){
		ramp = (m_duration -m_time) / m_fadeout;
	}
	else{
		ramp = 1.0;
	}
	samp = samp *ramp;
	
	
	//m_vibrato_phase += (2 * PI * m_vibrato) * GetSamplePeriod();
	//m_phase += (2 * PI *(m_freq + m_depth * sin(m_vibrato_phase))) * GetSamplePeriod();
	//m_phase += 2 * PI * m_freq * GetSamplePeriod();
	m_frame[1] = m_frame[0] = samp;

	return true;
}

double CAddSines::CrossFade(double samp){
	/*double frac = m_time / m_duration;
	double next_wave;
	next_wave = sin(2 * PI*m_time*m_next_freq);

	double new_samp;
	new_samp = (1 - frac)*samp + frac*next_wave;
	return new_samp;*/
	return 0.0;
}
