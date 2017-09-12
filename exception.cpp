/*
	Author: Dung Ly Viet
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
