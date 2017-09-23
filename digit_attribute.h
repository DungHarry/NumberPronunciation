/*
    Author: Dung Harry
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the DigitAttribute class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_DIGIT_ATTRIBUTE_H_
#define _COC_COC_NUMBER_PRONUNCIATION_DIGIT_ATTRIBUTE_H_

#include "attribute.h"
#include <utility>
#include <memory>
#include <string>

#define DIGIT_ATTRIBUTE_DIGIT_INVALID_VALUE (static_cast<char>('\0'))

class DigitAttribute : public Attribute {
public:
	DigitAttribute();
    DigitAttribute(AttributeType eType, int16_t iId, char cDigit, const wchar_t *cpcPronunciation);
	virtual ~DigitAttribute();

	virtual char getDigit();
	virtual void setDigit(const char cDigit);

    virtual const wchar_t* getPronunciation();
    virtual void setPronunciation(const wchar_t *cpcPronunciation);

	virtual bool less(const Comparable &attr);
	virtual bool equal(const Comparable &attr);
protected:
    unique_ptr<pair<char, unique_ptr<wstring>>> m_upCouple;
};

#endif
