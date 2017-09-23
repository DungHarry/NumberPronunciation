/*
    Author: Dung Harry
    Date created: September 22th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the ConditionAppendDigitsEndAttribute class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_CONDITION_APPEND_DIGITS_END_ATTRIBUTE_H_
#define _COC_COC_NUMBER_PRONUNCIATION_CONDITION_APPEND_DIGITS_END_ATTRIBUTE_H_

#include <utility>
#include <memory>
#include <string>
#include "attribute.h"

#define CONDITION_APPEND_DIGITS_END_ATTRIBUTE_INVALID_UNITS (static_cast<int16_t>(-1))

class ConditionAppendDigitsEndAttribute : public Attribute {
public:
    ConditionAppendDigitsEndAttribute();
    ConditionAppendDigitsEndAttribute(int16_t iId, int16_t iPosition, const wchar_t *cpwcDigitsEnd, const wchar_t *cpwcPronunciation);
    virtual ~ConditionAppendDigitsEndAttribute();

    virtual int16_t getUnits();
    virtual void setUnits(const int16_t iUnits);

    virtual const wchar_t* getDigitsEnd();
    virtual void setDigitsEnd(const wchar_t *cpwcDigitsEnd);

    virtual const wchar_t* getPronunciation();
    virtual void setPronunciation(const wchar_t *cpwcPronunciation);

    virtual bool less(const Comparable &attr);
    virtual bool equal(const Comparable &attr);
private:
    int16_t m_iUnits;
    unique_ptr<wstring> m_upDigitsEnd;
    unique_ptr<wstring> m_upPronunciation;
};

#endif

