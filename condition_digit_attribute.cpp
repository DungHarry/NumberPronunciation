/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the ConditionDigitAttribute class in C++ programming language
*/

#include "condition_digit_attribute.h"

ConditionDigitAttribute::ConditionDigitAttribute() :
	DigitAttribute(),
	m_iPosition(CONDITION_DIGIT_ATTRIBUTE_POSITION_INVLAID_VALUE)
{
	this->m_eType = ATTRIBUTE_TYPE_CONDITION_DIGIT; 
}

ConditionDigitAttribute::ConditionDigitAttribute(int16_t iPosition, int16_t iId, char cDigit, const char *cpcPronunciation) :
	DigitAttribute(ATTRIBUTE_TYPE_CONDITION_DIGIT, iId, cDigit, cpcPronunciation),
	m_iPosition(iPosition)
{

}

ConditionDigitAttribute::~ConditionDigitAttribute() {

}

int16_t ConditionDigitAttribute::getPosition() {
	return this->m_iPosition;
}

void ConditionDigitAttribute::setPosition(const int16_t iPosition) {
	this->m_iPosition = iPosition;
}