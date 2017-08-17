/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the NormalDigit class in C++ programming language
*/

#include "normal_digit.h"

NormalDigit::NormalDigit(char cValue, int16_t iPosition) :
	Digit(cValue, iPosition)
{

}

NormalDigit::~NormalDigit() {

}

bool NormalDigit::isValid() {
	return false;
}