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

	Description: this is the source code file of the NormalDigitAttribute class in C++ programming language
*/

#include "normal_digit_attribute.h"

NormalDigitAttribute::NormalDigitAttribute() :
	DigitAttribute()
{

}

NormalDigitAttribute::NormalDigitAttribute(int16_t iId, char cDigit, const wchar_t *cpcPronunciation) :
	DigitAttribute(ATTRIBUTE_TYPE_NORMAL_DIGIT, iId, cDigit, cpcPronunciation)
{

}

NormalDigitAttribute::NormalDigitAttribute(const NormalDigitAttribute &digitAttribute) :
DigitAttribute(ATTRIBUTE_TYPE_NORMAL_DIGIT, digitAttribute.m_iId, digitAttribute.m_upCouple.get() == nullptr ? DIGIT_ATTRIBUTE_DIGIT_INVALID_VALUE : digitAttribute.m_upCouple->first, digitAttribute.m_upCouple.get() == nullptr || digitAttribute.m_upCouple->second.get() == nullptr ? nullptr : digitAttribute.m_upCouple->second->c_str())
{

}

NormalDigitAttribute::~NormalDigitAttribute() {

}
