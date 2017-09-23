/*
    Author: Dung Harry
	Date created: August 31th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Data class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_DATA_H_
#define _COC_COC_NUMBER_PRONUNCIATION_DATA_H_

#include "base.h"
#include "global.h"

class Data : public Base {
public:
	Data();
	Data(const DataType eDataType);
	virtual ~Data();

	virtual DataType getType();
	virtual void setType(const DataType eType);
protected:
	DataType m_eType;
};

#endif
