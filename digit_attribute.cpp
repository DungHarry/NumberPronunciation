/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the DigitAttribute class in C++ programming language
*/

#include "digit_attribute.h"

DigitAttribute::DigitAttribute() :
	Attribute(ATTRIBUTE_ID_INVALID_VALUE, ATTRIBUTE_TYPE_NORMAL_DIGIT),
    m_apCouple(new pair<char, auto_ptr<wstring>>(DIGIT_ATTRIBUTE_DIGIT_INVALID_VALUE, auto_ptr<wstring>(NULL)))
{

}

DigitAttribute::DigitAttribute(AttributeType eType, int16_t iId, char cDigit, const wchar_t *cpcPronunciation) :
	Attribute(iId, eType <= ATTRIBUTE_TYPE_NONE && eType > ATTRIBUTE_TYPE_CONDITION_DIGIT ? ATTRIBUTE_TYPE_NORMAL_DIGIT : eType),
    m_apCouple(new pair<char, auto_ptr<wstring>>(cDigit, auto_ptr<wstring>(cpcPronunciation == NULL ? NULL : new wstring(cpcPronunciation))))
{

}

DigitAttribute::~DigitAttribute() {
	if (this->m_apCouple.get() != NULL) {
		this->m_apCouple->second.reset();

		this->m_apCouple.reset();
	}
}

char DigitAttribute::getDigit() {
	return (this->m_apCouple.get() == NULL) ? DIGIT_ATTRIBUTE_DIGIT_INVALID_VALUE : this->m_apCouple->first;
}

void DigitAttribute::setDigit(const char cDigit) {
	if (this->m_apCouple.get() == NULL)
		return;

	this->m_apCouple->first = cDigit;
}

const wchar_t* DigitAttribute::getPronunciation() {
	return (this->m_apCouple.get() == NULL) ? NULL : ((this->m_apCouple->second.get() == NULL) ? NULL : this->m_apCouple->second->c_str());
}

void DigitAttribute::setPronunciation(const wchar_t *cpcPronunciation) {
	if (this->m_apCouple.get() == NULL)
		return;

	if (cpcPronunciation == NULL)
		this->m_apCouple->second.reset();
	else
        this->m_apCouple->second.reset(new wstring(cpcPronunciation));
}
