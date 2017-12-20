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
    Date created: September 13th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the InputException class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_INPUT_EXCEPTION_H_
#define _COC_COC_NUMBER_PRONUNCIATION_INPUT_EXCEPTION_H_

#include "exception.h"

enum InputExceptionReason {
    INPUT_EXCEPTION_REASON_NONE = 0,
    INPUT_EXCEPTION_REASON_EXCEED_TRY_COUNT,
    INPUT_EXCEPTION_REASON_COUNT
};

class InputException : public Exception {
public:
    InputException();
    InputException(InputExceptionReason eReason);
    InputException(const InputException &e);
    virtual ~InputException();

    InputExceptionReason getReason();
    void setReason(const InputExceptionReason eReason);
protected:
    InputExceptionReason m_eReason;

  private:
    bool autoGenerateMessage();
};

#endif

