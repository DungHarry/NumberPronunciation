/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the SpecialDigitAttribute class in C++ programming language
*/

#include "special_digit_attribute.h"

SpecialDigitAttribute::SpecialDigitAttribute() :
	DigitAttribute()
{
	this->m_eType = ATTRIBUTE_TYPE_SPECIAL_DIGIT;
}

SpecialDigitAttribute::SpecialDigitAttribute(int16_t iId, char cDigit, const wchar_t*cpcPronunciation) :
	DigitAttribute(ATTRIBUTE_TYPE_SPECIAL_DIGIT, iId, cDigit, cpcPronunciation)
{

}

SpecialDigitAttribute::SpecialDigitAttribute(const SpecialDigitAttribute &digitAttribute) :
	DigitAttribute(ATTRIBUTE_TYPE_SPECIAL_DIGIT, digitAttribute.m_iId, digitAttribute.m_apCouple.get() == NULL ? DIGIT_ATTRIBUTE_DIGIT_INVALID_VALUE : digitAttribute.m_apCouple->first, digitAttribute.m_apCouple.get() == NULL || digitAttribute.m_apCouple->second.get() == NULL ? NULL : digitAttribute.m_apCouple->second->c_str())
{

}

SpecialDigitAttribute::~SpecialDigitAttribute() {

}
