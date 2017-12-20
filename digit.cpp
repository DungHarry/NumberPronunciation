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

	Description: this is the source code file of the Digit class in C++ programming language
*/

#include "digit.h"

Digit::Digit() :
	Object(OBJECT_TYPE_NORMAL_DIGIT),
	m_cValue(DIGIT_VALUE_INVALID_VALUE),
	m_iPosition(DIGIT_POSITION_INVALID_VALUE),
	m_bIgnore(false)
{

}

Digit::Digit(ObjectType eType, char cValue, int16_t iPosition) :
	Object(eType != OBJECT_TYPE_NORMAL_DIGIT && eType != OBJECT_TYPE_SPECIAL_DIGIT ? OBJECT_TYPE_NORMAL_DIGIT : eType),
	m_cValue(cValue),
	m_iPosition(iPosition),
	m_bIgnore(false)
{

}

Digit::~Digit() {

}

char Digit::getValue() {
	return this->m_cValue;
}

void Digit::setValue(const char cValue) {
	this->m_cValue = cValue;
}

int16_t Digit::getPosition() {
	return this->m_iPosition;
}

void Digit::setPosition(const int16_t iPosition) {
	this->m_iPosition;
}

bool Digit::getIgnore() {
	return this->m_bIgnore;
}

void Digit::setIgnore(const bool bIgnore) {
	this->m_bIgnore = bIgnore;
}

bool Digit::isValid() {
	return false;
}
