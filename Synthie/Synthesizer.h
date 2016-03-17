#pragma once
#include <list>
#include<vector>
#include "Instrument.h"
#include "Note.h"
#include "msxml2.h"
#include "xmlhelp.h"
#include "OddSinesFactory.h"
#include "WaveInstrumentFactory.h"
#include "AdditiveFactory.h"

using namespace std;

class CSynthesizer
{
public:
	CSynthesizer();
	virtual ~CSynthesizer();

public:
	//! Number of audio channels
	int GetNumChannels() { return m_channels; }

	//! Sample rate in samples per second
	double GetSampleRate() { return m_sampleRate; }

	//! Sample period in seconds (1/samplerate)
	double GetSamplePeriod() { return m_samplePeriod; }

	//! Set the number of channels
	void SetNumChannels(int n) { m_channels = n; }

	//! Set the sample rate
	void SetSampleRate(double s) { m_sampleRate = s;  m_samplePeriod = 1.0 / s; }

	//! Start the synthesizer
	void CSynthesizer::Start(void);

	//! Generate one audio frame
	bool CSynthesizer::Generate(double * frame);

	//! Get the time since we started generating audio
	double GetTime() { return m_time; }

	double GetBeatsPerMin(){ return m_bpm; }

	void CSynthesizer::Clear(void)
	{
		m_instruments.clear();
		m_notes.clear();
	}
	void CSynthesizer::OpenScore(CString & filename);
	

private:
	int		m_channels;
	double	m_sampleRate;
	double	m_samplePeriod;
	double m_time;

	double  m_bpm;                  //!< Beats per minute
	int     m_beatspermeasure;  //!< Beats per measure
	double  m_secperbeat;        //!< Seconds per beat

	int m_currentNote;          //!< The current note we are playing
	int m_measure;              //!< The current measure
	double m_beat;              //!< The current beat within the measure

	std::vector<CNote> m_notes;

	COddSinesFactory m_oddsinesfactory;
	CWaveInstrumentFactory m_waveinstfactory;

	CAdditiveFactory m_additivefactory;

private:
	std::list<CInstrument *>  m_instruments;
	void CSynthesizer::XmlLoadScore(IXMLDOMNode * xml);
	void CSynthesizer::XmlLoadInstrument(IXMLDOMNode * xml);
	void CSynthesizer::XmlLoadNote(IXMLDOMNode * xml, std::wstring & instrument, wstring& waveform);
};

