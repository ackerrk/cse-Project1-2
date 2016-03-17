#pragma once
#include "AudioNode.h"
#include <vector>
using namespace std;

class CAddSines :
	public CAudioNode
{
public:
	CAddSines();
	~CAddSines();

public:
	virtual void Start();
	virtual bool Generate();

	void SetFreq(double f){ m_freq = f; }
	void SetAmplitude(double a) { m_amp= a; }
	void AddHarmonic(int size,int i,double h){ 
		if (m_harmonics.size() == 0){
			for (int i = 0; i < size; i++){
				m_harmonics.push_back(1.0);
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
	double m_amp; //fundamental amplitude
	vector<double> m_harmonics; //list of harmonics wanted to be added together
	double m_vibrato;//vibrato rate
	double m_depth;//vibrato depth
	double m_vibrato_phase;
	double m_time;
};

