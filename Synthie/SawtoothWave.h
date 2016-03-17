#pragma once

#include "Basewave.h"
#include <vector>

class CSawtoothWave : public BaseWave
{
public:
	CSawtoothWave();
	virtual ~CSawtoothWave();
	//! Start audio generation
	virtual void Start() override;

	//! Generate one frame of audio
	virtual bool Generate() override;
	virtual void SetWavetables();
};