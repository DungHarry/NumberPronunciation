/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Digit class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_DIGIT_H_
#define _COC_COC_NUMBER_PRONUNCIATION_DIGIT_H_

#include "object.h"

#define DIGIT_VALUE_INVALID_VALUE (static_cast<char>('\0'))
#define DIGIT_POSITION_INVALID_VALUE (static_cast<int16_t>(-1))

class Digit : public Object {
public:
	Digit(char cValue = DIGIT_VALUE_INVALID_VALUE, int16_t iPosition = DIGIT_POSITION_INVALID_VALUE);
	virtual ~Digit();

	char getValue();
	void setValue(char cValue);

	int16_t getPosition();
	void setPosition(int16_t iPosition);

	virtual bool isValid();
private:
	int16_t m_iPosition;
	char m_cValue;
};

#endif