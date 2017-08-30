/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the ConditionAppendAttribute class in C++ programming language
*/

#include "condition_append_attribute.h"

ConditionAppendAttribute::ConditionAppendAttribute() :
	Attribute(ATTRIBUTE_ID_INVALID_VALUE, ATTRIBUTE_TYPE_CONDITION_APPEND),
    m_upCouple(new pair<int16_t, unique_ptr<wstring>>(CONDITION_APPEND_ATTRIBUTE_UNITS_INVLAID_VALUE, unique_ptr<wstring>(nullptr)))
{

}

ConditionAppendAttribute::ConditionAppendAttribute(int16_t iId, int16_t iPosition, const wchar_t *cpcPronunciation) :
	Attribute(iId, ATTRIBUTE_TYPE_CONDITION_APPEND),
    m_upCouple(new pair<int16_t, unique_ptr<wstring>>(iPosition, unique_ptr<wstring>(cpcPronunciation == nullptr ? nullptr : new wstring(cpcPronunciation))))
{

}

ConditionAppendAttribute::ConditionAppendAttribute(const ConditionAppendAttribute &attribute) :
	Attribute(attribute.m_iId, ATTRIBUTE_TYPE_CONDITION_APPEND),
    m_upCouple(new pair<int16_t, unique_ptr<wstring>>(attribute.m_upCouple.get() == nullptr ? CONDITION_APPEND_ATTRIBUTE_UNITS_INVLAID_VALUE : attribute.m_upCouple->first, unique_ptr<wstring>(attribute.m_upCouple.get() == nullptr || attribute.m_upCouple->second.get() == nullptr ? nullptr : new wstring(attribute.m_upCouple->second->c_str()))))
{

}

ConditionAppendAttribute::~ConditionAppendAttribute() {
	if (this->m_upCouple.get() != nullptr) {
		if (this->m_upCouple->second.get() != nullptr)
			this->m_upCouple->second.reset();

		this->m_upCouple.reset();
	}
}

int16_t ConditionAppendAttribute::getUnits() const {
    return (this->m_upCouple.get() == nullptr) ? CONDITION_APPEND_ATTRIBUTE_UNITS_INVLAID_VALUE : this->m_upCouple->first;
}

void ConditionAppendAttribute::setUnits(const int16_t iUnits) {
	if (this->m_upCouple.get() == nullptr)
		return;

    this->m_upCouple->first = iUnits;
}

const wchar_t *ConditionAppendAttribute::getPronunciation() {
	return (this->m_upCouple.get() == nullptr || this->m_upCouple->second.get() == nullptr) ? nullptr : this->m_upCouple->second->c_str();
}

void ConditionAppendAttribute::setPronunciation(const wchar_t *cpcPronunciation) {
	if (this->m_upCouple.get() == nullptr)
		return;

	if (cpcPronunciation == nullptr)
		this->m_upCouple->second.reset();
	else
        this->m_upCouple->second.reset(new wstring(cpcPronunciation));
}

bool ConditionAppendAttribute::less(const Comparable &attr) {
	const ConditionAppendAttribute *pConditionAppendAttribute = dynamic_cast<const ConditionAppendAttribute *>(&attr);

	return (pConditionAppendAttribute == nullptr || pConditionAppendAttribute->m_upCouple.get() == nullptr || this->m_upCouple.get() == nullptr) ? false : (this->m_upCouple->first < pConditionAppendAttribute->m_upCouple->first);
}

bool ConditionAppendAttribute::equal(const Comparable &attr) {
	const ConditionAppendAttribute *pConditionAppendAttribute = dynamic_cast<const ConditionAppendAttribute *>(&attr);

	return (pConditionAppendAttribute == nullptr || pConditionAppendAttribute->m_upCouple.get() == nullptr || this->m_upCouple.get() == nullptr) ? false : (this->m_upCouple->first == pConditionAppendAttribute->m_upCouple->first);
}