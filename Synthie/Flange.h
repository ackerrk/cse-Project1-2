#pragma once
#include "Effect.h"
class CFlange :
	public CEffect
{
public:
	CFlange();
	~CFlange();

	virtual void Process(double *frameIn, double *frameOut, double time) override;

	virtual void Start() override;

	virtual bool Generate() override;
private:
	int m_count;
};

