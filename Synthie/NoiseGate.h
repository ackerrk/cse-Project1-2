#pragma once
#include "Effect.h"
class CNoiseGate :
	public CEffect
{
public:
	CNoiseGate();
	virtual ~CNoiseGate();

	virtual void Process(double *frameIn, double *frameOut, double time) override;

	virtual void Start() override;

	virtual bool Generate() override;
};

