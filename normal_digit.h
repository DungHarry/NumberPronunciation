/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the NormalDigit class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_NORMAL_DIGIT_H_
#define _COC_COC_NUMBER_PRONUNCIATION_NORMAL_DIGIT_H_

#include "digit.h"

class NormalDigit : public Digit {
public:
	NormalDigit(char cValue = DIGIT_VALUE_INVALID_VALUE, int16_t iPosition = DIGIT_POSITION_INVALID_VALUE);
	virtual ~NormalDigit();

	virtual bool isValid();
};

#endif