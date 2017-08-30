/*
    Author: Dung Ly Viet
    Date created: August 21th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the MultipleDigitsAttribute class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_MULTIPLE_DIGITS_ATTRIBUTE_H_
#define _COC_COC_NUMBER_PRONUNCIATION_MULTIPLE_DIGITS_ATTRIBUTE_H_

#include "attribute.h"
#include <utility>
#include <memory>
#include <string>

class MultipleDigitsAttribute : public Attribute {
public:
    MultipleDigitsAttribute();
    MultipleDigitsAttribute(int16_t iId, const wchar_t *cpcDigits, const wchar_t *cpcPronunciation);
    MultipleDigitsAttribute(const MultipleDigitsAttribute &attr);
    virtual ~MultipleDigitsAttribute();

    virtual const wchar_t* getDigits();
    virtual void setDigits(const wchar_t *cpcDigits);

    virtual const wchar_t* getPronunciation();
    virtual void setPronunciation(const wchar_t *cpcPronunciation);

	virtual bool less(const Comparable &attr);
	virtual bool equal(const Comparable &attr);
private:
    unique_ptr<pair<unique_ptr<wstring>, unique_ptr<wstring>>> m_upCouple;
};

#endif
