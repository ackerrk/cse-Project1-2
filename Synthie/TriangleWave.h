#pragma once

#include "BaseWave.h"

class CTriangleWave : public BaseWave
{
public:
	CTriangleWave();
	virtual ~CTriangleWave();
	//! Start audio generation
	virtual void Start() override;

	//! Generate one frame of audio
	virtual bool Generate() override;
	virtual void SetWavetables() override;
};