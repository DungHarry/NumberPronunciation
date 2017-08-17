/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the ConditionDigitAttribute class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_CONDITION_DIGIT_ATTRIBUTE_H_
#define _COC_COC_NUMBER_PRONUNCIATION_CONDITION_DIGIT_ATTRIBUTE_H_

#include "digit_attribute.h"

#define CONDITION_DIGIT_ATTRIBUTE_POSITION_INVLAID_VALUE (static_cast<int16_t>(-1))

class ConditionDigitAttribute : public DigitAttribute {
public:
	ConditionDigitAttribute();
	ConditionDigitAttribute(int16_t iPosition, int16_t iId, char cDigit, const char *cpcPronunciation);
	virtual ~ConditionDigitAttribute();

	virtual int16_t getPosition();
	virtual void setPosition(const int16_t iPosition);

	virtual bool isValid();
private:
	int16_t m_iPosition;
};

#endif