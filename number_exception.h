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
	Date created: August 30th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the NumberException class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_NUMBER_EXCEPTION_H_
#define _COC_COC_NUMBER_PRONUNCIATION_NUMBER_EXCEPTION_H_

#include "exception.h"

enum NumberExceptionReason {
	NUMBER_EXCEPTION_REASON_NONE = 0,
	NUMBER_EXCEPTION_REASON_BAD_FORMAT,
	NUMBER_EXCEPTION_REASON_COUNT
};

class NumberException : public Exception {
public:
	NumberException();
	NumberException(const NumberExceptionReason eReason);
    NumberException(const NumberException &e);
	virtual ~NumberException();

	NumberExceptionReason getReason();
	void setReason(const NumberExceptionReason eReason);

protected:
	NumberExceptionReason m_eReason;

private:
    bool autoGenerateMessage();
};

#endif
