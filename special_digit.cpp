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

	Description: this is the source code file of the SpecialDigit class in C++ programming language
*/

#include "special_digit.h"

SpecialDigit::SpecialDigit() :
	Digit()
{
	this->m_eType = OBJECT_TYPE_SPECIAL_DIGIT;
}

SpecialDigit::SpecialDigit(char cValue, int16_t iPosition) :
	Digit(OBJECT_TYPE_SPECIAL_DIGIT, cValue, iPosition)
{
	this->m_eType = OBJECT_TYPE_SPECIAL_DIGIT;
}

SpecialDigit::SpecialDigit(const SpecialDigit &digit) {
	this->m_eType = digit.m_eType;
	this->m_iPosition = digit.m_iPosition;
	this->m_cValue = digit.m_cValue;
}

SpecialDigit::~SpecialDigit() {

}
