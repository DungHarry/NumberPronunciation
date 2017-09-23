/*
    Author: Dung Harry
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the SpecialDigitAttribute class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_SPECIAL_DIGIT_ATTRIBUTE_H_
#define _COC_COC_NUMBER_PRONUNCIATION_SPECIAL_DIGIT_ATTRIBUTE_H_

#include "digit_attribute.h"

class SpecialDigitAttribute : public DigitAttribute {
public:
	SpecialDigitAttribute();
    SpecialDigitAttribute(int16_t iId, char cDigit, const wchar_t*cpcPronunciation);
	SpecialDigitAttribute(const SpecialDigitAttribute &digitAttribute);
	virtual ~SpecialDigitAttribute();
};

#endif
