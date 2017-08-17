/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the SpecialDigit class in C++ programming language
*/

#include "special_digit.h"

SpecialDigit::SpecialDigit() :
	Digit()
{
	this->m_eType = OBJECT_TYPE_SPECIAL_DIGIT;
}

SpecialDigit::SpecialDigit(char cValue, int16_t iPosition) :
	Digit(OBJECT_TYPE_SPECIAL_DIGIT, cValue, iPosition)
{
	this->m_eType = OBJECT_TYPE_SPECIAL_DIGIT;
}

SpecialDigit::SpecialDigit(const SpecialDigit &digit) {
	this->m_eType = digit.m_eType;
	this->m_iPosition = digit.m_iPosition;
	this->m_cValue = digit.m_cValue;
}

SpecialDigit::~SpecialDigit() {

}