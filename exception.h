/*
	Author: Dung Ly Viet
	Date created: August 30th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Exception class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_EXCEPTION_H_
#define _COC_COC_NUMBER_PRONUNCIATION_EXCEPTION_H_

#include <string>
#include <memory>
#include <exception>
#include "global.h"
#include "base.h"

class Exception : public Base, public exception {
public:
	Exception();
	Exception(ExceptionType eType, const char *cpcMessage);
	virtual ~Exception();

	virtual const char* what() const throw();

	void setMessage(const char *cpcMessage);
protected:
	ExceptionType m_eType;

	unique_ptr<string> m_upsMessage;
};

#endif