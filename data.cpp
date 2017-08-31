/*
	Author: Dung Ly Viet
	Date created: August 31th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the Data class in C++ programming language
*/

#include "data.h"

Data::Data() :
	m_eType (DATA_TYPE_NONE)
{

}

Data::~Data() {

}

DataType Data::getType() {
	return this->m_eType;
}

void Data::setType(const DataType eType) {
	if (eType < DATA_TYPE_NONE || eType >= DATA_TYPE_COUNT)
		return;

	this->m_eType = eType;
}