#include "stdafx.h"
#include "SubtractiveInstrument.h"
#include "Note.h"
#include "Notes.h"
#include "SubtractiveEnvelope.h"
#include "SubtractiveADSREnvelope.h"


CSubtractiveInstrument::CSubtractiveInstrument()
{
	mDuration = 0.1;
	mResonFilter = false;
	mFilterEnvelope = false;
	mADSREnvelope = false;
}


CSubtractiveInstrument::~CSubtractiveInstrument()
{
}

void CSubtractiveInstrument::Start()
{
	mTime = 0;
	
	if (mWaveform == Sawtooth)
	{
		mSawtooth.SetSampleRate(GetSampleRate());
		mSawtooth.Start();
		if (mResonFilter && mFilterEnvelope)
		{
			mSubtractiveReson.SetSource(&mSawtooth);
			mSubtractivePitchFilter.SetSource(&mSubtractiveReson);
			mSubtractiveAmplitudeFilter.SetSource(&mSubtractiveAmplitudeFilter);
		}

		else if (mResonFilter)
		{
			mSubtractiveReson.SetSource(&mSawtooth);
			mSubtractiveAmplitudeFilter.SetSource(&mSubtractiveReson);
		}

		else if (mFilterEnvelope)
		{
			mSubtractivePitchFilter.SetSource(&mSawtooth);
			mSubtractiveAmplitudeFilter.SetSource(&mSubtractivePitchFilter);
		}
		else
		{
			mSubtractiveAmplitudeFilter.SetSource(&mSawtooth);
		}
	}

	else if (mWaveform == Triangle)
	{
		mTriangle.SetSampleRate(GetSampleRate());
		mTriangle.Start();
		if (mResonFilter && mFilterEnvelope)
		{
			mSubtractiveReson.SetSource(&mTriangle);
			mSubtractivePitchFilter.SetSource(&mSubtractiveReson);
			mSubtractiveAmplitudeFilter.SetSource(&mSubtractiveAmplitudeFilter);
		}
		else if (mResonFilter)
		{
			mSubtractiveReson.SetSource(&mTriangle);
			mSubtractiveAmplitudeFilter.SetSource(&mSubtractivePitchFilter);
		}
		else if (mFilterEnvelope)
		{
			mSubtractivePitchFilter.SetSource(&mTriangle);
			mSubtractiveAmplitudeFilter.SetSource(&mSubtractivePitchFilter);
		}
		else
		{
			mSubtractiveAmplitudeFilter.SetSource(&mTriangle);
		}
	} 

	else if (mWaveform == Square)
	{
		mSquare.SetSampleRate(GetSampleRate());
		mSquare.Start();
		if (mResonFilter && mFilterEnvelope)
		{
			mSubtractiveReson.SetSource(&mSquare);
			mSubtractivePitchFilter.SetSource(&mSubtractiveReson);
			mSubtractiveAmplitudeFilter.SetSource(&mSubtractiveAmplitudeFilter);
		}
		else if (mResonFilter)
		{
			mSubtractiveReson.SetSource(&mSquare);
			mSubtractiveAmplitudeFilter.SetSource(&mSubtractiveReson);
		}
		else if (mFilterEnvelope)
		{
			mSubtractivePitchFilter.SetSource(&mSquare);
			mSubtractiveAmplitudeFilter.SetSource(&mSubtractivePitchFilter);
		}
		else
		{
			mSubtractiveAmplitudeFilter.SetSource(&mSquare);
		}

	}


	mSubtractiveEnvelope = new CSubtractiveADSREnvelope();

	if (mResonFilter)
	{
		ResonFilterSetup();
	}
	if (mFilterEnvelope)
	{
		mSubtractivePitchFilter.SetEnvelope(mSubtractiveEnvelope);
		mSubtractivePitchFilter.SetSampleRate(GetSampleRate());
		mSubtractivePitchFilter.SetDuration(mDuration);
		mSubtractivePitchFilter.Start();
	}

	mSubtractiveAmplitudeFilter.SetEnvelope(mSubtractiveEnvelope);
	mSubtractiveAmplitudeFilter.SetSampleRate(GetSampleRate());
	mSubtractiveAmplitudeFilter.SetDuration(mDuration);
	mSubtractiveAmplitudeFilter.Start();

}

void CSubtractiveInstrument::SetNote(CNote *note)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	StringToWaveform(note->Waveform());

	// Loop over the list of attributes
	for (int i = 0; i < len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		// Get the value of the attribute.  A CComVariant is a variable
		// that can have any type. It loads the attribute value as a
		// string (UNICODE), but we can then change it to an integer 
		// (VT_I4) or double (VT_R8) using the ChangeType function 
		// and then read its integer or double value from a member variable.
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			// number of beats * seconds per beat = seconds for note
			SetDuration(value.dblVal);
		}
		else if (name == "note")
		{
			SetFreq(NoteToFrequency(value.bstrVal));
		}

		if (name == "resonfrequency")
		{
			mResonFilter = true;
			value.ChangeType(VT_R8);
			mResonFrequency = value.dblVal;
		}

//		if (name == "resonbandwidth")
//		{
//			value.ChangeType(VT_R8);
//			mResonBandwidth = value.dblVal;
//		}
//
//		if (name == "filter-envelope")
//		{
//			mFilterEnvelope = true;
//		}
	}
}

bool CSubtractiveInstrument::Generate()
{
	if (mWaveform == Sawtooth)
	{
		mSawtooth.Generate();
	}
	else if (mWaveform == Triangle)
	{
		mTriangle.Generate();
	}
	else if (mWaveform == Square)
	{
		mSquare.Generate();
	}
	
	auto valid = mSubtractiveAmplitudeFilter.Generate();
	// Read the component's sample and make it our resulting frame.
	m_frame[0] = mSubtractiveAmplitudeFilter.Frame(0);
	m_frame[1] = mSubtractiveAmplitudeFilter.Frame(1);
	// Update time
	mTime += GetSamplePeriod();
	// We return true until the time reaches the duration.

	return valid;
}

void CSubtractiveInstrument::SetFreq(double f)
{
	mSawtooth.SetFreq(f);
	mTriangle.SetFreq(f);
	mSquare.SetFreq(f);
}

void CSubtractiveInstrument::SetAmplitude(double a)
{
	mSawtooth.SetAmplitude(a);
	mTriangle.SetAmplitude(a);
	mSquare.SetAmplitude(a);
}

void CSubtractiveInstrument::StringToWaveform(std::wstring waveform)
{
	if (waveform == L"sawtooth")
	{
		mWaveform = Sawtooth;
	}
	else if (waveform == L"triangle")
	{
		mWaveform = Triangle;
	}
	else if (waveform == L"square")
	{
		mWaveform = Square;
	}
}

void CSubtractiveInstrument::ResonFilterSetup()
{
	mSubtractiveReson.SetEnvelope(mSubtractiveEnvelope);
	mSubtractiveReson.SetBandwidth(mResonBandwidth);
	mSubtractiveReson.SetFrequency(mResonFrequency);
	mSubtractiveReson.SetSampleRate(GetSampleRate());
	mSubtractiveReson.SetDuration(mDuration);
	mSubtractiveReson.Start();
}

