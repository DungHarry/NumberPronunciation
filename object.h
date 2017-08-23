/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Object class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_OBJECT_H_
#define _COC_COC_NUMBER_PRONUNCIATION_OBJECT_H_

#include "global.h"
#include "base.h"

class Object : public Base {
public:
	Object();
	Object(ObjectType eType);
	virtual ~Object();

	virtual ObjectType getType();
	virtual void setType(const ObjectType eType);

	virtual bool isValid();
protected:
	ObjectType m_eType;
};

#endif
