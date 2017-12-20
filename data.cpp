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
	Date created: August 31th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the Data class in C++ programming language
*/

#include "data.h"

Data::Data() :
	m_eType (DATA_TYPE_NONE)
{

}

Data::Data(const DataType eDataType) :
	m_eType (eDataType < DATA_TYPE_NONE || eDataType >= DATA_TYPE_COUNT ? DATA_TYPE_NONE : eDataType)
{

}

Data::~Data() {

}

DataType Data::getType() {
	return this->m_eType;
}

void Data::setType(const DataType eType) {
	if (eType < DATA_TYPE_NONE || eType >= DATA_TYPE_COUNT)
		return;

	this->m_eType = eType;
}
