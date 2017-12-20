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

    Description: this is the header file of the NullDeleter class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_NULL_DELETER_H_
#define _COC_COC_NUMBER_PRONUNCIATION_NULL_DELETER_H_

#include "deleter.h"

template <class T>
class NullDeleter : public Deleter<T> {
public:
    NullDeleter() :
    Deleter<T>(DELETER_TYPE_NULL)
    {

    }

    virtual ~NullDeleter() {

    }

    virtual void operator()(T *pPointer) {

    }
};

#endif
