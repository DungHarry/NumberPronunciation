/*
    Author: Dung Harry
    Date created: September 22th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the ConditionAppendDigitsEndAttribute class in C++ programming language
*/

#include "condition_append_digits_end_attribute.h"

ConditionAppendDigitsEndAttribute::ConditionAppendDigitsEndAttribute() :
    Attribute (ATTRIBUTE_ID_INVALID_VALUE, ATTRIBUTE_TYPE_CONDITION_APPEND_DIGITS_END),
    m_iUnits (CONDITION_APPEND_DIGITS_END_ATTRIBUTE_INVALID_UNITS),
    m_upDigitsEnd (nullptr),
    m_upPronunciation (nullptr)
{

}

ConditionAppendDigitsEndAttribute::ConditionAppendDigitsEndAttribute(int16_t iId, int16_t iPosition, const wchar_t *cpwcDigitsEnd, const wchar_t *cpwcPronunciation) :
    Attribute (iId, ATTRIBUTE_TYPE_CONDITION_APPEND_DIGITS_END),
    m_iUnits (iPosition),
    m_upDigitsEnd (cpwcDigitsEnd == nullptr ? nullptr : new wstring(cpwcDigitsEnd)),
    m_upPronunciation (cpwcPronunciation == nullptr ? nullptr : new wstring(cpwcPronunciation))
{

}

ConditionAppendDigitsEndAttribute::~ConditionAppendDigitsEndAttribute() {
    if(this->m_upDigitsEnd.get() != nullptr)
        this->m_upDigitsEnd.reset();

    if(this->m_upPronunciation.get() != nullptr)
        this->m_upPronunciation.reset();
}

int16_t ConditionAppendDigitsEndAttribute::getUnits() {
    return this->m_iUnits;
}

void ConditionAppendDigitsEndAttribute::setUnits(const int16_t iUnits) {
    if(iUnits < 0)
        return;

    this->m_iUnits = iUnits;
}

const wchar_t* ConditionAppendDigitsEndAttribute::getDigitsEnd() {
    return (this->m_upDigitsEnd.get() == nullptr ? nullptr : this->m_upDigitsEnd->c_str());
}

void ConditionAppendDigitsEndAttribute::setDigitsEnd(const wchar_t *cpwcDigitsEnd) {
    this->m_upDigitsEnd.reset(cpwcDigitsEnd == nullptr ? nullptr : new wstring(cpwcDigitsEnd));
}

const wchar_t* ConditionAppendDigitsEndAttribute::getPronunciation() {
    return (this->m_upPronunciation.get() == nullptr ? nullptr : this->m_upPronunciation->c_str());
}

void ConditionAppendDigitsEndAttribute::setPronunciation(const wchar_t *cpwcPronunciation) {
    this->m_upPronunciation.reset(cpwcPronunciation == nullptr ? nullptr : new wstring(cpwcPronunciation));
}

bool ConditionAppendDigitsEndAttribute::less(const Comparable &attr) {
    const ConditionAppendDigitsEndAttribute *pConditionAppendDigitsEndAttribute = dynamic_cast<const ConditionAppendDigitsEndAttribute *>(&attr);

    return (pConditionAppendDigitsEndAttribute == nullptr) ? true : (this->m_iUnits < pConditionAppendDigitsEndAttribute->m_iUnits || (this->m_upDigitsEnd.get() == nullptr || this->m_upDigitsEnd.get() == nullptr ? true : wcscmp(this->m_upDigitsEnd->c_str(), pConditionAppendDigitsEndAttribute->m_upDigitsEnd->c_str()) < 0));
}

bool ConditionAppendDigitsEndAttribute::equal(const Comparable &attr) {
    const ConditionAppendDigitsEndAttribute *pConditionAppendDigitsEndAttribute = dynamic_cast<const ConditionAppendDigitsEndAttribute *>(&attr);
    int32_t iCompareResult;

    return (pConditionAppendDigitsEndAttribute == nullptr) ? false : (this->m_iUnits == pConditionAppendDigitsEndAttribute->m_iUnits && (this->m_upDigitsEnd.get() == nullptr || this->m_upDigitsEnd.get() == nullptr ? true : wcscmp(this->m_upDigitsEnd->c_str(), pConditionAppendDigitsEndAttribute->m_upDigitsEnd->c_str()) == 0));
}
