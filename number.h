/*
	Author: Dung Ly Viet
	Date created: August 25th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Number class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_NUMBER_H_
#define _COC_COC_NUMBER_PRONUNCIATION_NUMBER_H_

#include <memory>
#include <vector>
#include "object.h"

#define NUMBER_LOWEST_UNIT_INVALID_VALUE (static_cast<int32_t>(-1))

class Number : public Object {
public:
	Number();
	Number(const int32_t iLowestUnit);
	virtual ~Number();

	virtual int32_t getLowestUnit();
	virtual void setLowestUnit(const int32_t iLowestUnit);

	virtual vector<auto_ptr<Object>>* getNumbers();
protected:
	int32_t m_iLowestUnit;
	auto_ptr<vector<auto_ptr<Object>>> m_apNumbers;
};

#endif