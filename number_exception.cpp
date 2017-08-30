/*
	Author: Dung Ly Viet
	Date created: August 30th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the NumberException class in C++ programming language
*/

#include "number_exception.h"

NumberException::NumberException() :
	Exception (EXCEPTION_TYPE_NUMBER, "Number exception common"),
	m_eReason (NUMBER_EXCEPTION_REASON_NONE)
{

}

NumberException::NumberException(const NumberExceptionReason eReason) :
	Exception(EXCEPTION_TYPE_NUMBER, "Number exception common"),
	m_eReason(eReason < NUMBER_EXCEPTION_REASON_NONE || eReason >= NUMBER_EXCEPTION_REASON_COUNT ? NUMBER_EXCEPTION_REASON_NONE : eReason)
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