/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the base Object class in C++ programming language
*/

#include "object.h"

Object::Object() :
	m_eType (OBJECT_TYPE_NONE)
{

}

Object::Object(ObjectType eType) :
	m_eType (eType <= OBJECT_TYPE_NONE || eType >= OBJECT_TYPE_COUNT ? OBJECT_TYPE_NONE : eType)
{

}

Object::~Object() {

}

ObjectType Object::getType() {
	return this->m_eType;
}

void Object::setType(const ObjectType eType) {
	if (this->m_eType <= OBJECT_TYPE_NONE || this->m_eType >= OBJECT_TYPE_COUNT)
		return;

	this->m_eType = eType;
}