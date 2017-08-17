/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the NormalDigitAttribute class in C++ programming language
*/

#include "normal_digit_attribute.h"

NormalDigitAttribute::NormalDigitAttribute() :
	DigitAttribute()
{

}

NormalDigitAttribute::NormalDigitAttribute(int16_t iId, char cDigit, const char *cpcPronunciation) :
	DigitAttribute(ATTRIBUTE_TYPE_NORMAL_DIGIT, iId, cDigit, cpcPronunciation)
{

}

NormalDigitAttribute::NormalDigitAttribute(const NormalDigitAttribute &digitAttribute) :
DigitAttribute(ATTRIBUTE_TYPE_NORMAL_DIGIT, digitAttribute.m_iId, digitAttribute.m_apCouple.get() == NULL ? DIGIT_ATTRIBUTE_DIGIT_INVALID_VALUE : digitAttribute.m_apCouple->first, digitAttribute.m_apCouple.get() == NULL || digitAttribute.m_apCouple->second.get() == NULL ? NULL : digitAttribute.m_apCouple->second->c_str())
{

}

NormalDigitAttribute::~NormalDigitAttribute() {

}