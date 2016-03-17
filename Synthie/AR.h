#pragma once
#include "AudioNode.h"
class CAR :
	public CAudioNode
{
public:
	CAR();
	virtual ~CAR();

	void SetSource(CAudioNode* const &source){m_source = source;}
	void SetDuration(double d){ m_duration = d; }
	void SetAttack(double a){m_attack = a;}
	void SetRelease(double r){ m_release = r; }
	virtual void Start();
	virtual bool Generate();

private:
	double m_attack;
	double m_release;
	double m_duration;
	double m_time;
	double m_amplitude_factor;

	CAudioNode* m_source;
};

