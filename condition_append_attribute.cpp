/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the ConditionAppendAttribute class in C++ programming language
*/

#include "condition_append_attribute.h"

ConditionAppendAttribute::ConditionAppendAttribute() :
	Attribute(ATTRIBUTE_ID_INVALID_VALUE, ATTRIBUTE_TYPE_CONDITION_APPEND),
	m_apCouple(new pair<int16_t, auto_ptr<string>>(CONDITION_APPEND_ATTRIBUTE_POSITION_INVLAID_VALUE, auto_ptr<string>(NULL)))
{

}

ConditionAppendAttribute::ConditionAppendAttribute(int16_t iId, int16_t iPosition, const char *cpcPronunciation) :
	Attribute(iId, ATTRIBUTE_TYPE_CONDITION_APPEND),
	m_apCouple(new pair<int16_t, auto_ptr<string>>(iPosition, auto_ptr<string>(cpcPronunciation == NULL ? NULL : new string(cpcPronunciation))))
{

}

ConditionAppendAttribute::ConditionAppendAttribute(const ConditionAppendAttribute &attribute) :
	Attribute(attribute.m_iId, ATTRIBUTE_TYPE_CONDITION_APPEND),
	m_apCouple(new pair<int16_t, auto_ptr<string>>(attribute.m_apCouple ))
{

}

ConditionAppendAttribute::~ConditionAppendAttribute() {
	if (this->m_apCouple.get() != NULL) {
		if (this->m_apCouple->second.get() != NULL)
			this->m_apCouple->second.reset();

		this->m_apCouple.reset();
	}
}

int16_t ConditionAppendAttribute::getPosition() {
	return (this->m_apCouple.get() == NULL) ? CONDITION_APPEND_ATTRIBUTE_POSITION_INVLAID_VALUE : this->m_apCouple->first;
}

void ConditionAppendAttribute::setPosition(const int16_t iPosition) {
	if (this->m_apCouple.get() == NULL)
		return;

	this->m_apCouple->first = iPosition;
}

const char* ConditionAppendAttribute::getPronunciation() {
	return (this->m_apCouple.get() == NULL || this->m_apCouple->second.get() == NULL) ? NULL : this->m_apCouple->second->c_str();
}

void ConditionAppendAttribute::setPronunciation(const char *cpcPronunciation) {
	if (this->m_apCouple.get() == NULL)
		return;

	if (cpcPronunciation == NULL)
		this->m_apCouple->second.reset();
	else
		this->m_apCouple->second.reset(new string(cpcPronunciation));
}

bool ConditionAppendAttribute::compare(const Base &b) {
	const ConditionAppendAttribute *pAttribute = dynamic_cast<const ConditionAppendAttribute *>(&b);

	return (pAttribute == NULL) ? false : 
}