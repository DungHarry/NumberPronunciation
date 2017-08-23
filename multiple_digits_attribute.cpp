/*
    Author: Dung Ly Viet
    Date created: August 21th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the MultipleDigitsAttribute class in C++ programming language
*/

#include "multiple_digits_attribute.h"

MultipleDigitsAttribute::MultipleDigitsAttribute() :
    Attribute (),
    m_apCouple (new pair<auto_ptr<wstring>, auto_ptr<wstring>>(auto_ptr<wstring>(NULL), auto_ptr<wstring>(NULL)))
{

}

MultipleDigitsAttribute::MultipleDigitsAttribute(int16_t iId, const wchar_t*cpcDigits, const wchar_t*cpcPronunciation) :
    Attribute (iId, ATTRIBUTE_TYPE_MULTIPLE_DIGITS),
    m_apCouple (new pair<auto_ptr<wstring>, auto_ptr<wstring>>(auto_ptr<wstring>(cpcDigits == NULL ? NULL : new wstring(cpcDigits)), auto_ptr<wstring>(cpcPronunciation == NULL ? NULL : new wstring(cpcPronunciation))))
{

}

MultipleDigitsAttribute::MultipleDigitsAttribute(const MultipleDigitsAttribute &attr) :
    Attribute (attr.m_iId, ATTRIBUTE_TYPE_MULTIPLE_DIGITS),
    m_apCouple (new pair<auto_ptr<wstring>, auto_ptr<wstring>>(auto_ptr<wstring>(attr.m_apCouple.get() == NULL || attr.m_apCouple->first.get() == NULL ? NULL : new wstring(attr.m_apCouple->first->c_str())), auto_ptr<wstring>(attr.m_apCouple.get() == NULL || attr.m_apCouple->second.get() == NULL ? NULL : new wstring(attr.m_apCouple->second->c_str()))))
{

}

MultipleDigitsAttribute::~MultipleDigitsAttribute() {
    if(this->m_apCouple.get() != NULL) {
        if(this->m_apCouple->first.get() != NULL)
            this->m_apCouple->first.reset();

        if(this->m_apCouple->second.get() != NULL)
            this->m_apCouple->second.reset();

        this->m_apCouple.reset();
    }
}

const wchar_t *MultipleDigitsAttribute::getDigits() {
    return (this->m_apCouple.get() == NULL || this->m_apCouple->first.get() == NULL) ? NULL : this->m_apCouple->first->c_str();
}

void MultipleDigitsAttribute::setDigits(const wchar_t *cpcDigits) {
    if(this->m_apCouple.get() == NULL)
        return;

    this->m_apCouple->first.reset(cpcDigits == NULL ? NULL : new wstring(cpcDigits));
}

const wchar_t *MultipleDigitsAttribute::getPronunciation() {
    return (this->m_apCouple.get() == NULL || this->m_apCouple->second.get() == NULL) ? NULL : this->m_apCouple->second->c_str();
}

void MultipleDigitsAttribute::setPronunciation(const wchar_t *cpcPronunciation) {
    if(this->m_apCouple.get() == NULL)
        return;

    this->m_apCouple->second.reset(cpcPronunciation == NULL ? NULL : new wstring(cpcPronunciation));
}
