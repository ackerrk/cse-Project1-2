#include "stdafx.h"
#include "AR.h"


CAR::CAR()
{
	m_attack = 0.05;
	m_release = 0.05;
	m_duration = m_attack + m_release; //full duration is attack plus release
	m_time = 0.0;
	m_amplitude_factor = 1.0;
}


CAR::~CAR()
{
}

void CAR::Start(){
	m_source->SetSampleRate(GetSampleRate());
	m_source->Start();//run start for source--sinewave
	m_time = 0;
}

bool CAR::Generate(){
	m_source->Generate(); //run generate for source--sinewave

	//write in frames--by checking time
	//if less than attach time then take in account attack
	if (m_time < m_attack){
		m_frame[0] = m_source->Frame(0)*m_time/m_attack;
		m_frame[1] = m_source->Frame(1)*m_time/m_attack;
		m_amplitude_factor = 1;

		
	}
	/*else if (m_time < (m_attack)+.25){
		//if during first .5s then increase volume x6 and slowly decay until at normal amplitude (factor *1)
		//comment test5
		m_amplitude_factor = 1.5;
		for (double i = 0.0; i < .25; i +=.01){
			m_frame[0] = m_source->Frame(0)*m_amplitude_factor;
			m_frame[1] = m_source->Frame(1)*m_amplitude_factor;
			m_amplitude_factor -= .06;
		}
	}*/
	//if during normal time treat like normal--mroe than attack but less than total duration -release
	else if (m_time < (m_time-m_release))
	{
		m_amplitude_factor = 1.0;
		m_frame[0] = m_source->Frame(0);
		m_frame[1] = m_source->Frame(1);
		
	}
	//else during release time
	else
	{
		m_frame[0] = m_source->Frame(0) * (m_duration - m_time) / m_release;
		m_frame[1] = m_source->Frame(1) * (m_duration - m_time) / m_release;
	}


	// Update time
	m_time += GetSamplePeriod();

	// We return true until the time reaches the duration.
	return m_time < m_duration;
}
