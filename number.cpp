/*
	Author: Dung Ly Viet
	Date created: August 25th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the Number class in C++ programming language
*/

#include "number.h"

Number::Number() : 
	m_iLowestUnit(NUMBER_LOWEST_UNIT_INVALID_VALUE),
	m_apNumbers(new vector<auto_ptr<Object>>())
{

}

Number::Number(const int32_t iLowestUnit) :
	m_iLowestUnit(iLowestUnit < 0 ? NUMBER_LOWEST_UNIT_INVALID_VALUE : iLowestUnit),
	m_apNumbers(new vector<auto_ptr<Object>>())
{

}

Number::~Number() {
	if (this->m_apNumbers.get() != NULL) {
		this->m_apNumbers->clear();

		this->m_apNumbers.reset();
	}
}

int32_t Number::getLowestUnit() {
	return this->m_iLowestUnit;
}

void Number::setLowestUnit(const int32_t iLowestUnit) {
	if (this->m_iLowestUnit < 0)
		return;

	this->m_iLowestUnit = iLowestUnit;
}

vector<auto_ptr<Object>>* Number::getNumbers() {
	return this->m_apNumbers.get();
}
