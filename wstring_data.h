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

    Description: this is the header file of the WStringData class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_WSTRING_DATA_H_
#define _COC_COC_NUMBER_PRONUNCIATION_WSTRING_DATA_H_

#include <memory>
#include <string>
#include "data.h"

class WStringData : public Data {
public:
    WStringData();
    WStringData(const wchar_t *cpwcValue);
    WStringData(const WStringData &ws);
    virtual ~WStringData();

    const wchar_t* getValue();
    void setValue(const wchar_t *cpwcValue);
protected:
    unique_ptr<wstring> m_upwsValue;
};

#endif
