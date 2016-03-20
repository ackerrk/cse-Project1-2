#pragma once
#include "AudioNode.h"
#include "Note.h"
#include "SubtractiveAmplitudeFilter.h"

class CSynthesizer;

class CInstrument :
	public CAudioNode
{
public:
	CInstrument();
	virtual ~CInstrument();

	virtual void SetNote(CNote *note) = 0;

	void SetSynthesizer(CSynthesizer* s){ m_synth = s; }

	double Send(int i) { return m_sends[i]; }
	void SetSend(int i, double value) { m_sends[i] = value; }

private:
	CSynthesizer* m_synth = nullptr;

protected:
	CSubtractiveAmplitudeFilter mSubtractiveAmplitudeFilter;
	CSubtractiveEnvelope* mSubtractiveEnvelope;
	double m_sends[5];
};

