#pragma once
#include "Effect.h"
class CReverb :
	public CEffect
{
public:
	CReverb();
	virtual ~CReverb();

	virtual void Process(double *frameIn, double *frameOut, double time) override;

	virtual void Start() override;

	virtual bool Generate() override;

private:
	double m_reverb[2];
};

