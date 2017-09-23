/*
    Author: Dung Harry
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the NormalDigitAttribute class in C++ programming language
*/

#include "normal_digit_attribute.h"

NormalDigitAttribute::NormalDigitAttribute() :
	DigitAttribute()
{

}

NormalDigitAttribute::NormalDigitAttribute(int16_t iId, char cDigit, const wchar_t *cpcPronunciation) :
	DigitAttribute(ATTRIBUTE_TYPE_NORMAL_DIGIT, iId, cDigit, cpcPronunciation)
{

}

NormalDigitAttribute::NormalDigitAttribute(const NormalDigitAttribute &digitAttribute) :
DigitAttribute(ATTRIBUTE_TYPE_NORMAL_DIGIT, digitAttribute.m_iId, digitAttribute.m_upCouple.get() == nullptr ? DIGIT_ATTRIBUTE_DIGIT_INVALID_VALUE : digitAttribute.m_upCouple->first, digitAttribute.m_upCouple.get() == nullptr || digitAttribute.m_upCouple->second.get() == nullptr ? nullptr : digitAttribute.m_upCouple->second->c_str())
{

}

NormalDigitAttribute::~NormalDigitAttribute() {

}
