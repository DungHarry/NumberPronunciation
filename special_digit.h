/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the SpecialDigit class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_SPECIAL_DIGIT_H_
#define _COC_COC_NUMBER_PRONUNCIATION_SPECIAL_DIGIT_H_

#include "digit.h"

class SpecialDigit : public Digit {
public:
	SpecialDigit(char cValue = DIGIT_VALUE_INVALID_VALUE, int16_t iPosition = DIGIT_POSITION_INVALID_VALUE);
	virtual ~SpecialDigit();

	virtual bool isValid();
};

#endif