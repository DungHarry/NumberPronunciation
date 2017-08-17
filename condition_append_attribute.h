/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the ConditionAppendAttribute class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_CONDITION_APPEND_ATTRIBUTE_H_
#define _COC_COC_NUMBER_PRONUNCIATION_CONDITION_APPEND_ATTRIBUTE_H_

#include "attribute.h"
#include <utility>
#include <memory>
#include <string>

#define CONDITION_APPEND_ATTRIBUTE_POSITION_INVLAID_VALUE (static_cast<int16_t>(-1))

class ConditionAppendAttribute : public Attribute {
public:
	ConditionAppendAttribute();
	ConditionAppendAttribute(int16_t iId, int16_t iPosition, const char *cpcPronunciation);
	ConditionAppendAttribute(const ConditionAppendAttribute &attribute);
	virtual ~ConditionAppendAttribute();

	virtual int16_t getPosition();
	virtual void setPosition(const int16_t iPosition);

	virtual const char* getPronunciation();
	virtual void setPronunciation(const char *cpcPronunciation);
private:
	auto_ptr<pair<int16_t, auto_ptr<string>>> m_apCouple;
};

#endif