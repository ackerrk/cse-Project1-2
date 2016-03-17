#pragma once

#include "BaseWave.h"
#include <vector>

class CSquareWave : public BaseWave
{
public:
	CSquareWave();
	virtual ~CSquareWave();
	//! Start audio generation
	virtual void Start() override;

	//! Generate one frame of audio
	virtual bool Generate() override;
	virtual void SetWavetables() override;
};