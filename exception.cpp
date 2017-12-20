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

	Description: this is the header file of the Exception class in C++ programming language
*/

#include "exception.h"

Exception::Exception() :
	m_eType(EXCEPTION_TYPE_NONE),
	m_upsMessage(new string("Common exception"))
{

}

Exception::Exception(ExceptionType eType, const char *cpcMessage) :
	m_eType(eType < EXCEPTION_TYPE_NONE || eType >= EXCEPTION_TYPE_COUNT ? EXCEPTION_TYPE_NONE : eType),
	m_upsMessage(new string(cpcMessage == nullptr ? "Common exception" : cpcMessage))
{

}

Exception::Exception(const Exception &e) :
    m_eType(e.m_eType < EXCEPTION_TYPE_NONE || e.m_eType >= EXCEPTION_TYPE_COUNT ? EXCEPTION_TYPE_NONE : e.m_eType),
    m_upsMessage(new string(e.m_upsMessage.get() == nullptr ? "Common exception" : e.m_upsMessage->c_str()))
{

}

Exception::~Exception() {
	this->m_upsMessage.reset();
}

const char* Exception::what() const throw() {
	return (this->m_upsMessage.get() == nullptr) ? "Common exception" : this->m_upsMessage->c_str();
}

void Exception::setMessage(const char *cpcMessage) {
	if (cpcMessage == nullptr)
		return;

	this->m_upsMessage.reset(new string(cpcMessage));
}
