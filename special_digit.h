/*
    Author: Dung Harry
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the SpecialDigit class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_SPECIAL_DIGIT_H_
#define _COC_COC_NUMBER_PRONUNCIATION_SPECIAL_DIGIT_H_

#include "digit.h"

class SpecialDigit : public Digit {
public:
	SpecialDigit();
	SpecialDigit(char cValue, int16_t iPosition);
	SpecialDigit(const SpecialDigit &digit);
	virtual ~SpecialDigit();
};

#endif
