/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the Digit class in C++ programming language
*/

#include "digit.h"

Digit::Digit() :
	Object(OBJECT_TYPE_NORMAL_DIGIT),
	m_cValue(DIGIT_VALUE_INVALID_VALUE),
	m_iPosition(DIGIT_POSITION_INVALID_VALUE)
{

}

Digit::Digit(ObjectType eType, char cValue, int16_t iPosition) :
	Object(eType != OBJECT_TYPE_NORMAL_DIGIT && eType != OBJECT_TYPE_SPECIAL_DIGIT ? OBJECT_TYPE_NORMAL_DIGIT : eType),
	m_cValue(cValue),
	m_iPosition(iPosition)
{

}

Digit::~Digit() {

}

char Digit::getValue() {
	return this->m_cValue;
}

void Digit::setValue(const char cValue) {
	this->m_cValue = cValue;
}

int16_t Digit::getPosition() {
	return this->m_iPosition;
}

void Digit::setPosition(const int16_t iPosition) {
	this->m_iPosition;
}

bool Digit::isValid() {
	return false;
}