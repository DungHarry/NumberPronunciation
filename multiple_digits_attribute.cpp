/*
    Author: Dung Ly Viet
    Date created: August 21th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the MultipleDigitsAttribute class in C++ programming language
*/

#include "multiple_digits_attribute.h"

MultipleDigitsAttribute::MultipleDigitsAttribute() :
    Attribute (),
    m_upCouple (new pair<unique_ptr<wstring>, unique_ptr<wstring>>(unique_ptr<wstring>(nullptr), unique_ptr<wstring>(nullptr)))
{

}

MultipleDigitsAttribute::MultipleDigitsAttribute(int16_t iId, const wchar_t*cpcDigits, const wchar_t*cpcPronunciation) :
    Attribute (iId, ATTRIBUTE_TYPE_MULTIPLE_DIGITS),
    m_upCouple (new pair<unique_ptr<wstring>, unique_ptr<wstring>>(unique_ptr<wstring>(cpcDigits == nullptr ? nullptr : new wstring(cpcDigits)), unique_ptr<wstring>(cpcPronunciation == nullptr ? nullptr : new wstring(cpcPronunciation))))
{

}

MultipleDigitsAttribute::MultipleDigitsAttribute(const MultipleDigitsAttribute &attr) :
    Attribute (attr.m_iId, ATTRIBUTE_TYPE_MULTIPLE_DIGITS),
    m_upCouple (new pair<unique_ptr<wstring>, unique_ptr<wstring>>(unique_ptr<wstring>(attr.m_upCouple.get() == nullptr || attr.m_upCouple->first.get() == nullptr ? nullptr : new wstring(attr.m_upCouple->first->c_str())), unique_ptr<wstring>(attr.m_upCouple.get() == nullptr || attr.m_upCouple->second.get() == nullptr ? nullptr : new wstring(attr.m_upCouple->second->c_str()))))
{

}

MultipleDigitsAttribute::~MultipleDigitsAttribute() {
    if(this->m_upCouple.get() != nullptr) {
        if(this->m_upCouple->first.get() != nullptr)
            this->m_upCouple->first.reset();

        if(this->m_upCouple->second.get() != nullptr)
            this->m_upCouple->second.reset();

        this->m_upCouple.reset();
    }
}

const wchar_t *MultipleDigitsAttribute::getDigits() {
    return (this->m_upCouple.get() == nullptr || this->m_upCouple->first.get() == nullptr) ? nullptr : this->m_upCouple->first->c_str();
}

void MultipleDigitsAttribute::setDigits(const wchar_t *cpcDigits) {
    if(this->m_upCouple.get() == nullptr)
        return;

    this->m_upCouple->first.reset(cpcDigits == nullptr ? nullptr : new wstring(cpcDigits));
}

const wchar_t *MultipleDigitsAttribute::getPronunciation() {
    return (this->m_upCouple.get() == nullptr || this->m_upCouple->second.get() == nullptr) ? nullptr : this->m_upCouple->second->c_str();
}

void MultipleDigitsAttribute::setPronunciation(const wchar_t *cpcPronunciation) {
    if(this->m_upCouple.get() == nullptr)
        return;

    this->m_upCouple->second.reset(cpcPronunciation == nullptr ? nullptr : new wstring(cpcPronunciation));
}

bool MultipleDigitsAttribute::less(const Comparable &attr) {
	const MultipleDigitsAttribute *pMultipleDigitsAttribute = dynamic_cast<const MultipleDigitsAttribute *>(&attr);

	return (pMultipleDigitsAttribute == nullptr || pMultipleDigitsAttribute->m_upCouple.get() == nullptr || pMultipleDigitsAttribute->m_upCouple->first.get() == nullptr || this->m_upCouple.get() == nullptr || this->m_upCouple->first.get() == nullptr) ? false : (wcscmp(this->m_upCouple->first->c_str(), pMultipleDigitsAttribute->m_upCouple->first->c_str()) < 0);
}

bool MultipleDigitsAttribute::equal(const Comparable &attr) {
	const MultipleDigitsAttribute *pMultipleDigitsAttribute = dynamic_cast<const MultipleDigitsAttribute *>(&attr);

	return (pMultipleDigitsAttribute == nullptr || pMultipleDigitsAttribute->m_upCouple.get() == nullptr || pMultipleDigitsAttribute->m_upCouple->first.get() == nullptr || this->m_upCouple.get() == nullptr || this->m_upCouple->first.get() == nullptr) ? false : (wcscmp(this->m_upCouple->first->c_str(), pMultipleDigitsAttribute->m_upCouple->first->c_str()) == 0);
}
