/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the Digit class in C++ programming language
*/

#include "digit.h"

Digit::Digit(char cValue, int16_t iPosition) : 
	Object(OBJECT_TYPE_NORMAL_DIGIT),
	m_cValue(cValue),
	m_iPosition(iPosition)
{

}

Digit::~Digit() {

}

char Digit::getValue() {
	return this->m_cValue;
}

void Digit::setValue(char cValue) {
	this->m_cValue = cValue;
}

int16_t Digit::getPosition() {
	return this->m_iPosition;
}

void Digit::setPosition(int16_t iPosition) {
	this->m_iPosition;
}

bool Digit::isValid() {
	return false;
}