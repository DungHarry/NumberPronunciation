/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Base class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_HANDLER_H_
#define _COC_COC_NUMBER_PRONUNCIATION_HANDLER_H_

#include "global.h"
#include "base.h"
#include "executable.h"

class Handler : public Base, public Executable {
public:
	Handler();
    Handler(HandlerType eType);
	virtual ~Handler();

    virtual bool execute();

    HandlerType getType();
    void setType(HandlerType eType);
protected:
    HandlerType m_eType;
};

#endif
