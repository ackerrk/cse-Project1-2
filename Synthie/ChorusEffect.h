#pragma once
#include "Effect.h"
class CChorusEffect :
	public CEffect
{
public:
	CChorusEffect();
	virtual ~CChorusEffect();

	virtual void Start() override;

	virtual bool Generate() override;

	virtual void Process(double *input, double *output, double time) override;
};

