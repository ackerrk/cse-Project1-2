#pragma once
#include "AudioNode.h"
#include <vector>
using namespace std;

class COrganSines :
	public CAudioNode
{
public:
	COrganSines();
	~COrganSines();

public:
	virtual void Start();
	virtual bool Generate();

	void SetFreq(double f){ m_freq = f; }
	void SetAmplitude(int i, double a) {
		if (m_amps.size() == 0){
			for (int i = 0; i < 9; i++){
				m_amps.push_back(0);
			}
		}

		m_amps[i] = a;
	}
	void AddHarmonic(int i, double h){
		if (m_harmonics.size() == 0){
			for (int i = 0; i < 9; i++){
				m_harmonics.push_back(0);
			}
		}
		//int harmonic = h;
		m_harmonics[i] = h;
	}

	void SetVibrato(double rate){ m_vibrato = rate; }
	void SetVibratoDepth(double d){ m_depth = d; }
	void SetTime(double t){ m_time = t; }

private:
	double m_freq; //fundamental freq
	double m_phase; //phase shift
	vector<double> m_amps; //list of harmonics wanted to be added together
	vector<double> m_harmonics; //list of harmonics wanted to be added together
	double m_vibrato;//vibrato rate
	double m_depth;//vibrato depth
	double m_vibrato_phase;
	double m_time;
};

