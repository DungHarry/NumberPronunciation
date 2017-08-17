/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the Attribute class in C++ programming language
*/

#include "attribute.h"

Attribute::Attribute() :
	m_iId(ATTRIBUTE_ID_INVALID_VALUE),
	m_eType(ATTRIBUTE_TYPE_NONE)
{

}

Attribute::Attribute(int16_t iId, AttributeType eType) :
	m_iId(iId),
	m_eType(eType <= ATTRIBUTE_TYPE_NONE || eType >= ATTRIBUTE_TYPE_COUNT ? ATTRIBUTE_TYPE_NONE : eType)
{

}

Attribute::~Attribute() {

}

AttributeType Attribute::getType() {
	return this->m_eType;
}

void Attribute::setType(const AttributeType eType) {
	if (eType <= ATTRIBUTE_TYPE_NONE || eType >= ATTRIBUTE_TYPE_COUNT)
		return;

	this->m_eType = eType;
}

int16_t Attribute::getId() {
	return this->m_iId;
}

void Attribute::setId(const int16_t iId) {
	this->m_iId = iId;
}

bool Attribute::operator< (const Attribute &attribute) {
	return this->m_iId < attribute.m_iId;
}