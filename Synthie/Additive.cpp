#include "stdafx.h"
#include "Additive.h"
#include "Notes.h"


CAdditive::CAdditive()
{
}


CAdditive::~CAdditive()
{
}

void CAdditive::Start()
{
	m_ar.SetSource(&m_sines);
	m_ar.SetSampleRate(GetSampleRate());
	m_ar.Start();
	m_time = 0;
	m_vibrato = 0.;
	m_vibrato_depth = 0.;
	m_crossfading = false;
	m_next_freq = 0.0;
}

void CAdditive::SetNote(CNote* note)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i < len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			SetDuration(value.dblVal);
			m_sines.SetDur(value.dblVal);
		}
		else if (name == "note")
		{
			SetFreq(NoteToFrequency(value.bstrVal));
		}
		else if (name == "attack")
		{
			value.ChangeType(VT_R8);
			m_ar.SetAttack(value.dblVal);
		}
		else if (name == "release")
		{
			value.ChangeType(VT_R8);
			m_ar.SetRelease(value.dblVal);
		}
		else if (name == "vibrato"){
			value.ChangeType(VT_R8);
			m_vibrato = (value.dblVal);
			m_sines.SetVibrato(m_vibrato);
		}
		else if (name == "depth"){
			value.ChangeType(VT_R8);
			m_vibrato_depth = (value.dblVal);
			m_sines.SetVibratoDepth(m_vibrato_depth);
		}
		else if (name == "crossfading"){
			value.ChangeType(VT_R8);
			if ((value.dblVal) == 1.0){
				m_crossfading = true;
			}
		}
		else if (name == "to"){
			m_next_freq = NoteToFrequency(value.bstrVal);
			m_sines.SetCrossfading(m_crossfading, m_next_freq);
		}
		else if (name == "fadeout"){
			value.ChangeType(VT_R8);
			double f = value.dblVal;
			m_sines.SetFadeout(f);
		}
		else if (name == "fadein"){
			value.ChangeType(VT_R8);
			double f = value.dblVal;
			m_sines.SetFadein(f);
		}
	}
}

bool CAdditive::Generate()
{
	bool valid = m_ar.Generate();

	m_frame[0] = m_ar.Frame(0);
	m_frame[1] = m_ar.Frame(1);

	m_time += GetSamplePeriod();
	m_sines.SetTime(m_time);

	m_sines.Generate();
	return valid;
}

