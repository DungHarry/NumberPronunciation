/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the SpecialDigit class in C++ programming language
*/

#include "special_digit.h"

SpecialDigit::SpecialDigit(char cValue, int16_t iPosition) :
	Digit(cValue, iPosition)
{

}

SpecialDigit::~SpecialDigit() {

}

bool SpecialDigit::isValid() {
	return false;
}