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

#include "number_exception.h"

NumberException::NumberException() :
	Exception (EXCEPTION_TYPE_NUMBER, "Number exception common"),
	m_eReason (NUMBER_EXCEPTION_REASON_NONE)
{
    this->autoGenerateMessage();
}

NumberException::NumberException(const NumberExceptionReason eReason) :
	Exception(EXCEPTION_TYPE_NUMBER, "Number exception common"),
	m_eReason(eReason < NUMBER_EXCEPTION_REASON_NONE || eReason >= NUMBER_EXCEPTION_REASON_COUNT ? NUMBER_EXCEPTION_REASON_NONE : eReason)
{
	this->autoGenerateMessage();
}

NumberException::NumberException(const NumberException &e) :
    Exception(e),
    m_eReason(e.m_eReason)
{
    this->autoGenerateMessage();
}

NumberException::~NumberException() {

}

NumberExceptionReason NumberException::getReason() {
	return this->m_eReason;
}

void NumberException::setReason(const NumberExceptionReason eReason) {
	if (eReason < NUMBER_EXCEPTION_REASON_NONE || eReason >= NUMBER_EXCEPTION_REASON_COUNT)
		return;

	this->m_eReason = eReason;

	this->autoGenerateMessage();
}

bool NumberException::autoGenerateMessage() {
	if (this->m_eReason < NUMBER_EXCEPTION_REASON_NONE || this->m_eReason >= NUMBER_EXCEPTION_REASON_COUNT)
		return false; 

	if (this->m_eReason == NUMBER_EXCEPTION_REASON_NONE)
		this->m_upsMessage.reset(new string("Number exception common"));
	else if (this->m_eReason == NUMBER_EXCEPTION_REASON_BAD_FORMAT)
		this->m_upsMessage.reset(new string("Bad number format"));
	else
		this->m_upsMessage.reset(new string("Unknown number exception"));

	return true;
}
