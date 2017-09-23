/*
    Author: Dung Harry
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the NormalDigit class in C++ programming language
*/

#include "normal_digit.h"

NormalDigit::NormalDigit() :
	Digit(OBJECT_TYPE_NORMAL_DIGIT, DIGIT_VALUE_INVALID_VALUE, DIGIT_POSITION_INVALID_VALUE)
{

}

NormalDigit::NormalDigit(char cValue, int16_t iPosition) :
	Digit(OBJECT_TYPE_NORMAL_DIGIT, cValue, iPosition)
{

}

NormalDigit::NormalDigit(const NormalDigit &digit) :
	Digit(digit.m_eType, digit.m_cValue, digit.m_iPosition)
{

}

NormalDigit::~NormalDigit() {

}
