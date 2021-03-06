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
    Date created: August 22th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the Utility class in C++ programming language
*/

#include "utility.h"

Utility::Utility() :
    m_eType (UTILITY_TYPE_NONE)
{

}

Utility::Utility(UtilityType eType) :
    m_eType (eType < 0 || eType >= UTILITY_TYPE_COUNT ? UTILITY_TYPE_NONE : eType)
{

}

Utility::~Utility() {

}

UtilityType Utility::getType() {
    return this->m_eType;
}

void Utility::setType(UtilityType eType) {
    if(eType < 0 || eType >= UTILITY_TYPE_COUNT)
        return;

    this->m_eType = eType;
}
