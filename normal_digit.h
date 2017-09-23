/*
    Author: Dung Harry
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the NormalDigit class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_NORMAL_DIGIT_H_
#define _COC_COC_NUMBER_PRONUNCIATION_NORMAL_DIGIT_H_

#include "digit.h"

class NormalDigit : public Digit {
public:
	NormalDigit();
	NormalDigit(char cValue, int16_t iPosition);
	NormalDigit(const NormalDigit &digit);
	virtual ~NormalDigit();
};

#endif
