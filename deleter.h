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
    Date created: September 18th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the Deleter class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_DELETER_H_
#define _COC_COC_NUMBER_PRONUNCIATION_DELETER_H_

#include "global.h"
#include "base.h"

template <class T>
class Deleter : public Base {
public:
    Deleter() :
    Base(),
    m_eType(DELETER_TYPE_NONE)
    {

    }

    Deleter(const DeleterType eType) :
    Base(),
    m_eType (eType < DELETER_TYPE_NONE || eType >= DELETER_TYPE_COUNT ? DELETER_TYPE_NONE : eType)
    {

    }

    virtual ~Deleter() {

    }

    virtual void operator()(T *pPointer) = 0;

    const DeleterType getType() {
        return this->m_eType;
    }

protected:
    DeleterType m_eType;
};

#endif
