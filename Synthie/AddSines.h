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
				m_harmonics.push_back(0.0);
			}
		}
		m_harmonics[i] = h;
		}
	void AddAmp(int size, int i, double a){
		if (m_harm_amps.size() == 0){
			for (int i = 0; i < size; i++){
				m_harm_amps.push_back(0.0);
			}
		}
		m_harm_amps[i] = a;
	}
	void SetVibrato(double rate){ m_vibrato = rate; }
	void SetVibratoDepth(double d){ m_depth = d; }
	void SetTime(double t){ m_time = t; }
	void SetCrossfading(bool c, double f){ m_crossfading = c; m_next_freq = f; }
	void SetDur(double d){ m_duration = d; }
	void SetFadeout(double fade){ m_fadeout = fade; }
	void SetFadein(double f){ m_fadein = f; }

private:
	double m_freq; //fundamental freq
	double m_phase; //phase shift
	double m_amp; //fundamental amplitude
	vector<double> m_harmonics; //list of harmonics wanted to be added together
	vector<double> m_harm_amps;
	double m_vibrato;//vibrato rate
	double m_depth;//vibrato depth
	double m_vibrato_phase;
	double m_time;
	double m_next_freq;
	bool m_crossfading;
	double m_duration;
	double m_fadein;
	double m_fadeout;

	double CrossFade(double samp);
};

