#include "stdafx.h"
#include "OrganFactory.h"


COrganFactory::COrganFactory()
{
	m_harmonics.push_back(1);
	m_vibrato = 0.;
	m_vibrato_depth = 0.;

	for (int i = 0; i < 9; i++){
		m_amps.push_back(0);
		m_harmonics.push_back(0);
	}
}


COrganFactory::~COrganFactory()
{
}

COrgan *COrganFactory::CreateInstrument(){
	COrgan *instrument = new COrgan();
	for (int i = 0; i < 9; i++){
		instrument->SetHarmonics(i, m_harmonics[i]);
	}

	for (int i = 0; i<9; i++)
	{
		instrument->SetAmplitude(i, m_amps[i]);
	}

	//instrument->SetVibrato(m_vibrato, m_vibrato_depth);
	return instrument;
}

void COrganFactory::SetNote(CNote *note)
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

		if (name == "drawbar"){
			value.ChangeType(VT_R8);
			int test = value.dblVal;
			getDrawbar(test);
		}
	}
}

void COrganFactory::getDrawbar(int num){
	int count = 0;
	
	for (int i = 0; i < 9; i++){
		if (num % 10 != 0){
			int diff = 8 - (num % 10);
			if (diff == 0){
				m_amps[8 - count] = 1;
			}else{
				double y = (diff * -3) / 20.0;
				m_amps[8 - count] = pow(10, y);
			}

			if (count == 0){
				m_harmonics[8] = 16;
			}else if(count == 1){
				m_harmonics[7] = 12;
			}
			else if (count == 2){
				m_harmonics[6] = 10;
			}
			else if (count == 3){
				m_harmonics[5] = 8;
			}
			else if (count == 4){
				m_harmonics[4] = 6;
			}
			else if (count == 5){
				m_harmonics[3] = 4;
			}
			else if (count == 6){
				m_harmonics[2] = 2;
			}
			else if (count == 7){
				m_harmonics[1] = 3;
			}
			else if (count == 8){
				m_harmonics[0] = 1;
			}
		}
		num = num / 10;
		count++;
	}
}
