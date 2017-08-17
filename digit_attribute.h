/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the DigitAttribute class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUMCIATION_DIGIT_ATTRIBUTE_H_
#define _COC_COC_NUMBER_PRONUNCIATION_DIGIT_ATTRIBUTE_H_

#include "attribute.h"
#include <utility>
#include <memory>
#include <string>

#define DIGIT_ATTRIBUTE_DIGIT_INVALID_VALUE (static_cast<char>('\0'))

class DigitAttribute : public Attribute {
public:
	DigitAttribute();
	DigitAttribute(AttributeType eType, int16_t iId, char cDigit, const char *cpcPronunciation);
	virtual ~DigitAttribute();

	virtual int16_t getId();
	virtual void setId(const int16_t iId); 

	virtual char getDigit();
	virtual void setDigit(const char cDigit);

	virtual const char* getPronunciation();
	virtual void setPronunciation(const char *cpcPronunciation);
protected:
	auto_ptr<pair<char, auto_ptr<string>>> m_apCouple;
};

#endif