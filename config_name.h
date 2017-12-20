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
    Date created: September 3rd, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the ConfigName class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_CONFIG_NAME_H_
#define _COC_COC_NUMBER_PRONUNCIATION_CONFIG_NAME_H_

#include <cstdint>
#include <memory>
#include <string>
#include "object.h"
#include "string_utility.h"
#include "comparable.h"

#define CONFIG_NAME_ID_INVALID_ID (static_cast<int16_t>(-1))

template <class T>
class ConfigName : public Object, public Comparable {
public:
    ConfigName();
    ConfigName(int16_t iId, const T *cpcValue);
    ConfigName(const ConfigName &cf);
    virtual ~ConfigName();

    const T* getValue();
    void setValue(const T *cpcValue);

    int16_t getId();
    void setId(const int16_t iId);

    virtual bool less(const Comparable &com);
    virtual bool equal(const Comparable &com);
protected:
    int16_t m_iId;
    unique_ptr<basic_string<T>> m_upsValue;
};

template class ConfigName<wchar_t>;

#endif

