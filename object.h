/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the base Object class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_OBJECT_H_
#define _COC_COC_NUMBER_PRONUNCIATION_OBJECT_H_

#include "global.h"
#include <string>
#include <memory>

using namespace std;

class Object {
public:
	Object();
	Object(ObjectType eType);
	virtual ~Object();

	ObjectType getType();
	void setType(const ObjectType eType);
protected:
	ObjectType m_eType;
};

#endif