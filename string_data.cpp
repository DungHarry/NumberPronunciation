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
    Date created: September 5th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the StringData class in C++ programming language
*/

#include "string_data.h"

StringData::StringData() :
    Data (DATA_TYPE_STRING),
    m_upsValue (new string(""))
{

}
StringData::StringData(const char *cpcValue) :
    Data (DATA_TYPE_STRING),
    m_upsValue (new string(cpcValue == nullptr ? "" : cpcValue))
{

}

StringData::StringData(const StringData &s) :
    Data(DATA_TYPE_STRING),
    m_upsValue (new string(s.m_upsValue.get() == nullptr ? "" : s.m_upsValue->c_str()))
{

}

StringData::~StringData() {
    if(this->m_upsValue.get() != nullptr)
        this->m_upsValue.reset();
}

const char* StringData::getValue() {
    return this->m_upsValue.get() == nullptr ? nullptr : this->m_upsValue->c_str();
}

void StringData::setValue(const char *cpcValue) {
    this->m_upsValue.reset(new string(cpcValue == nullptr ? "" : cpcValue));
}
