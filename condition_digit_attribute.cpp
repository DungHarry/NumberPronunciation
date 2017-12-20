/*
    NumberPronunciation provides a way to pronounce a number
    Copyright (C) 2017 of Dung Harry

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.

    Author: Dung Harry
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the ConditionDigitAttribute class in C++ programming language
*/

#include "condition_digit_attribute.h"

ConditionDigitAttribute::ConditionDigitAttribute() :
	DigitAttribute(),
	m_iPosition(CONDITION_DIGIT_ATTRIBUTE_POSITION_INVLAID_VALUE)
{
	this->m_eType = ATTRIBUTE_TYPE_CONDITION_DIGIT; 
}

ConditionDigitAttribute::ConditionDigitAttribute(int16_t iPosition, int16_t iId, char cDigit, const wchar_t *cpcPronunciation) :
	DigitAttribute(ATTRIBUTE_TYPE_CONDITION_DIGIT, iId, cDigit, cpcPronunciation),
	m_iPosition(iPosition)
{

}

ConditionDigitAttribute::~ConditionDigitAttribute() {

}

int16_t ConditionDigitAttribute::getPosition() {
	return this->m_iPosition;
}

void ConditionDigitAttribute::setPosition(const int16_t iPosition) {
	this->m_iPosition = iPosition;
}

bool ConditionDigitAttribute::less(const Comparable &attr) {
    const ConditionDigitAttribute *pConditionDigitAttribute = dynamic_cast<const ConditionDigitAttribute *>(&attr);

    return (pConditionDigitAttribute == nullptr || pConditionDigitAttribute->m_upCouple.get() == nullptr || this->m_upCouple.get() == nullptr) ? true : ((this->m_upCouple->first < pConditionDigitAttribute->m_upCouple->first) || (this->m_iPosition < pConditionDigitAttribute->m_iPosition));
}

bool ConditionDigitAttribute::equal(const Comparable &attr) {
    const ConditionDigitAttribute *pConditionDigitAttribute = dynamic_cast<const ConditionDigitAttribute *>(&attr);

    return (pConditionDigitAttribute == nullptr || pConditionDigitAttribute->m_upCouple.get() == nullptr || this->m_upCouple.get() == nullptr) ? false : ((this->m_upCouple->first == pConditionDigitAttribute->m_upCouple->first) && (this->m_iPosition == pConditionDigitAttribute->m_iPosition));
}

bool ConditionDigitAttribute::isValid() {
    return false;
}
