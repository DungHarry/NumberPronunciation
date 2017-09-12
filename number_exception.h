/*
	Author: Dung Ly Viet
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
private:
	bool autoGenerateMessage();

	NumberExceptionReason m_eReason;
};

#endif
