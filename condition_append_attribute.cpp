/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the ConditionAppendAttribute class in C++ programming language
*/

#include "condition_append_attribute.h"

ConditionAppendAttribute::ConditionAppendAttribute() :
	Attribute(ATTRIBUTE_ID_INVALID_VALUE, ATTRIBUTE_TYPE_CONDITION_APPEND),
    m_apCouple(new pair<int16_t, auto_ptr<wstring>>(CONDITION_APPEND_ATTRIBUTE_UNITS_INVLAID_VALUE, auto_ptr<wstring>(NULL)))
{

}

ConditionAppendAttribute::ConditionAppendAttribute(int16_t iId, int16_t iPosition, const wchar_t *cpcPronunciation) :
	Attribute(iId, ATTRIBUTE_TYPE_CONDITION_APPEND),
    m_apCouple(new pair<int16_t, auto_ptr<wstring>>(iPosition, auto_ptr<wstring>(cpcPronunciation == NULL ? NULL : new wstring(cpcPronunciation))))
{

}

ConditionAppendAttribute::ConditionAppendAttribute(const ConditionAppendAttribute &attribute) :
	Attribute(attribute.m_iId, ATTRIBUTE_TYPE_CONDITION_APPEND),
    m_apCouple(new pair<int16_t, auto_ptr<wstring>>(attribute.m_apCouple.get() == NULL ? CONDITION_APPEND_ATTRIBUTE_UNITS_INVLAID_VALUE : attribute.m_apCouple->first, auto_ptr<wstring>(attribute.m_apCouple.get() == NULL || attribute.m_apCouple->second.get() == NULL ? NULL : new wstring(attribute.m_apCouple->second->c_str()))))
{

}

ConditionAppendAttribute::~ConditionAppendAttribute() {
	if (this->m_apCouple.get() != NULL) {
		if (this->m_apCouple->second.get() != NULL)
			this->m_apCouple->second.reset();

		this->m_apCouple.reset();
	}
}

int16_t ConditionAppendAttribute::getUnits() {
    return (this->m_apCouple.get() == NULL) ? CONDITION_APPEND_ATTRIBUTE_UNITS_INVLAID_VALUE : this->m_apCouple->first;
}

void ConditionAppendAttribute::setUnits(const int16_t iUnits) {
	if (this->m_apCouple.get() == NULL)
		return;

    this->m_apCouple->first = iUnits;
}

const wchar_t *ConditionAppendAttribute::getPronunciation() {
	return (this->m_apCouple.get() == NULL || this->m_apCouple->second.get() == NULL) ? NULL : this->m_apCouple->second->c_str();
}

void ConditionAppendAttribute::setPronunciation(const wchar_t *cpcPronunciation) {
	if (this->m_apCouple.get() == NULL)
		return;

	if (cpcPronunciation == NULL)
		this->m_apCouple->second.reset();
	else
        this->m_apCouple->second.reset(new wstring(cpcPronunciation));
}
