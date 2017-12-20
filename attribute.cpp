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

	Description: this is the source code file of the Attribute class in C++ programming language
*/

#include "attribute.h"

Attribute::Attribute() :
	m_iId(ATTRIBUTE_ID_INVALID_VALUE),
	m_eType(ATTRIBUTE_TYPE_NONE)
{

}

Attribute::Attribute(int16_t iId, AttributeType eType) :
	m_iId(iId),
	m_eType(eType <= ATTRIBUTE_TYPE_NONE || eType >= ATTRIBUTE_TYPE_COUNT ? ATTRIBUTE_TYPE_NONE : eType)
{

}

Attribute::~Attribute() {

}

AttributeType Attribute::getType() {
	return this->m_eType;
}

void Attribute::setType(const AttributeType eType) {
	if (eType <= ATTRIBUTE_TYPE_NONE || eType >= ATTRIBUTE_TYPE_COUNT)
		return;

	this->m_eType = eType;
}

int16_t Attribute::getId() {
	return this->m_iId;
}

void Attribute::setId(const int16_t iId) {
	this->m_iId = iId;
}

bool Attribute::less(const Comparable &attr) {
	const Attribute *pAttr = dynamic_cast<const Attribute *>(&attr);

	return (pAttr == nullptr) ? false : (this->m_iId < pAttr->m_iId);
}

bool Attribute::equal(const Comparable &attr) {
	const Attribute *pAttr = dynamic_cast<const Attribute *>(&attr);

	return (pAttr == nullptr) ? false : (this->m_iId == pAttr->m_iId);
}
