#include "stdafx.h"
#include "AdditiveFactory.h"


CAdditiveFactory::CAdditiveFactory()
{
	m_harmonics.push_back(1);
	m_vibrato = 0.;
	m_vibrato_depth = 0.;
	m_harm_amps.push_back(1);
	
}


CAdditiveFactory::~CAdditiveFactory()
{
}

CAdditive *CAdditiveFactory::CreateInstrument(){
	CAdditive *instrument = new CAdditive();
	for (int i = 0; i < m_harmonics.size(); i++){
		instrument->SetHarmonics(m_harmonics.size(),i, m_harmonics[i]);
		instrument->SetAmps(m_harm_amps.size(), i, m_harm_amps[i]);
	}
	//instrument->SetVibrato(m_vibrato, m_vibrato_depth);
	return instrument;
}

void CAdditiveFactory::SetNote(CNote *note)
{

	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i<len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "h1"){
			value.ChangeType(VT_R8);
			m_harmonics[0] =value.dblVal;
		}
		else if (name == "h2"){
			value.ChangeType(VT_R8);
			m_harmonics.push_back(value.dblVal);
		}
		else if (name == "h3"){
			value.ChangeType(VT_R8);
			m_harmonics.push_back(value.dblVal);
		}
		else if (name == "h4"){
			value.ChangeType(VT_R8);
			m_harmonics.push_back(value.dblVal);
		}
		else if (name == "h5"){
			value.ChangeType(VT_R8);
			m_harmonics.push_back(value.dblVal);
		}
		else if (name == "h6"){
			value.ChangeType(VT_R8);
			m_harmonics.push_back(value.dblVal);
		}
		else if (name == "a1"){
			value.ChangeType(VT_R8);
			m_harm_amps[0] = value.dblVal;
		}
		else if (name == "a2"){
			value.ChangeType(VT_R8);
			m_harm_amps.push_back(value.dblVal);
		}
		else if (name == "a3"){
			value.ChangeType(VT_R8);
			m_harm_amps.push_back(value.dblVal);
		}
		else if (name == "a4"){
			value.ChangeType(VT_R8);
			m_harm_amps.push_back(value.dblVal);
		}
		else if (name == "a5"){
			value.ChangeType(VT_R8);
			m_harm_amps.push_back(value.dblVal);
		}
		else if (name == "a6"){
			value.ChangeType(VT_R8);
			m_harm_amps.push_back(value.dblVal);
		}
		
	}
}
