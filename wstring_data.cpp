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

    Description: this is the source code file of the WStringData class in C++ programming language
*/

#include "wstring_data.h"

WStringData::WStringData() :
    Data (DATA_TYPE_WSTRING),
    m_upwsValue (new wstring(L""))
{

}

WStringData::WStringData(const wchar_t *cpwcValue) :
    Data (DATA_TYPE_WSTRING),
    m_upwsValue (new wstring(cpwcValue == nullptr ? L"" : cpwcValue))
{

}

WStringData::WStringData(const WStringData &ws) :
    Data (DATA_TYPE_WSTRING),
    m_upwsValue (new wstring(ws.m_upwsValue.get() == nullptr ? L"" : ws.m_upwsValue->c_str()))
{

}

WStringData::~WStringData() {
    if(this->m_upwsValue.get() != nullptr)
        this->m_upwsValue.reset();
}

const wchar_t* WStringData::getValue() {
    return this->m_upwsValue.get() == nullptr ? nullptr : this->m_upwsValue->c_str();
}

void WStringData::setValue(const wchar_t *cpwcValue) {
    this->m_upwsValue.reset(new wstring(cpwcValue == nullptr ? L"" : cpwcValue));
}
