/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the NormalDigit class in C++ programming language
*/

#include "normal_digit.h"

NormalDigit::NormalDigit() :
	Digit()
{

}

NormalDigit::NormalDigit(AttributeType eType, char cValue, int16_t iPosition) :
	Digit(eType != ATTRIBUTE_TYPE_NORMAL_DIGIT && eType != ATTRIBUTE_TYPE_SPECIAL_DIGIT ? ATTRIBUTE_TYPE_NORMAL_DIGIT : eType, cValue, iPosition)
{

}

NormalDigit::NormalDigit(const NormalDigit &digit) {
	this->m_eType = digit.m_eType;
	this->m_cValue = digit.m_cValue;
	this->m_iPosition = digit.m_iPosition;
}

NormalDigit::~NormalDigit() {

}
