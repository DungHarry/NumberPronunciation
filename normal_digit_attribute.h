/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the NormalDigitAttribute class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_NORMAL_DIGIT_ATTRIBUTE_H_
#define _COC_COC_NUMBER_PRUNUNCIATION_NORMAL_DIGIT_ATTRIBUTE_H_

#include "digit_attribute.h"

class NormalDigitAttribute : public DigitAttribute {
public:
	NormalDigitAttribute();
    NormalDigitAttribute(int16_t iId, char cDigit, const wchar_t *cpcPronunciation);
	NormalDigitAttribute(const NormalDigitAttribute &digitAttribute);
	virtual ~NormalDigitAttribute();
};

#endif
