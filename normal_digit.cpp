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

	Description: this is the source code file of the NormalDigit class in C++ programming language
*/

#include "normal_digit.h"

NormalDigit::NormalDigit() :
	Digit(OBJECT_TYPE_NORMAL_DIGIT, DIGIT_VALUE_INVALID_VALUE, DIGIT_POSITION_INVALID_VALUE)
{

}

NormalDigit::NormalDigit(char cValue, int16_t iPosition) :
	Digit(OBJECT_TYPE_NORMAL_DIGIT, cValue, iPosition)
{

}

NormalDigit::NormalDigit(const NormalDigit &digit) :
	Digit(digit.m_eType, digit.m_cValue, digit.m_iPosition)
{

}

NormalDigit::~NormalDigit() {

}
