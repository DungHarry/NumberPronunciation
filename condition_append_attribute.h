/*
    Author: Dung Harry
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the ConditionAppendAttribute class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_CONDITION_APPEND_ATTRIBUTE_H_
#define _COC_COC_NUMBER_PRONUNCIATION_CONDITION_APPEND_ATTRIBUTE_H_

#include <utility>
#include <memory>
#include <string>
#include "attribute.h"

#define CONDITION_APPEND_ATTRIBUTE_UNITS_INVLAID_VALUE (static_cast<int16_t>(-1))

class ConditionAppendAttribute : public Attribute {
public:
	ConditionAppendAttribute();
    ConditionAppendAttribute(int16_t iId, int16_t iPosition, const wchar_t *cpcPronunciation);
	ConditionAppendAttribute(const ConditionAppendAttribute &attribute);
	virtual ~ConditionAppendAttribute();

    virtual int16_t getUnits() const;
    virtual void setUnits(const int16_t iUnits);

    virtual const wchar_t* getPronunciation();
    virtual void setPronunciation(const wchar_t *cpcPronunciation);

	virtual bool less(const Comparable &attr);
	virtual bool equal(const Comparable &attr);
private:
    unique_ptr<pair<int16_t, unique_ptr<wstring>>> m_upCouple;
};

#endif
