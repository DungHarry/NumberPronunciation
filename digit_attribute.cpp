/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the DigitAttribute class in C++ programming language
*/

#include "digit_attribute.h"

DigitAttribute::DigitAttribute() :
	Attribute(ATTRIBUTE_ID_INVALID_VALUE, ATTRIBUTE_TYPE_NORMAL_DIGIT),
    m_upCouple(new pair<char, unique_ptr<wstring>>(DIGIT_ATTRIBUTE_DIGIT_INVALID_VALUE, unique_ptr<wstring>(nullptr)))
{

}

DigitAttribute::DigitAttribute(AttributeType eType, int16_t iId, char cDigit, const wchar_t *cpcPronunciation) :
	Attribute(iId, eType <= ATTRIBUTE_TYPE_NONE && eType > ATTRIBUTE_TYPE_CONDITION_DIGIT ? ATTRIBUTE_TYPE_NORMAL_DIGIT : eType),
    m_upCouple(new pair<char, unique_ptr<wstring>>(cDigit, unique_ptr<wstring>(cpcPronunciation == nullptr ? nullptr : new wstring(cpcPronunciation))))
{

}

DigitAttribute::~DigitAttribute() {
	if (this->m_upCouple.get() != nullptr) {
		this->m_upCouple->second.reset();

		this->m_upCouple.reset();
	}
}

char DigitAttribute::getDigit() {
	return (this->m_upCouple.get() == nullptr) ? DIGIT_ATTRIBUTE_DIGIT_INVALID_VALUE : this->m_upCouple->first;
}

void DigitAttribute::setDigit(const char cDigit) {
	if (this->m_upCouple.get() == nullptr)
		return;

	this->m_upCouple->first = cDigit;
}

const wchar_t* DigitAttribute::getPronunciation() {
	return (this->m_upCouple.get() == nullptr) ? nullptr : ((this->m_upCouple->second.get() == nullptr) ? nullptr : this->m_upCouple->second->c_str());
}

void DigitAttribute::setPronunciation(const wchar_t *cpcPronunciation) {
	if (this->m_upCouple.get() == nullptr)
		return;

	if (cpcPronunciation == nullptr)
		this->m_upCouple->second.reset();
	else
        this->m_upCouple->second.reset(new wstring(cpcPronunciation));
}

bool DigitAttribute::less(const Comparable &attr) {
	const DigitAttribute *pDigitAttribute = dynamic_cast<const DigitAttribute *>(&attr);

	return (pDigitAttribute == nullptr || pDigitAttribute->m_upCouple.get() == nullptr || this->m_upCouple.get() == nullptr) ? false : (this->m_upCouple->first < pDigitAttribute->m_upCouple->first); 
}

bool DigitAttribute::equal(const Comparable &attr) {
	const DigitAttribute *pDigitAttribute = dynamic_cast<const DigitAttribute *>(&attr);

	return (pDigitAttribute == nullptr || pDigitAttribute->m_upCouple.get() == nullptr || this->m_upCouple.get() == nullptr) ? false : (this->m_upCouple->first == pDigitAttribute->m_upCouple->first);
}