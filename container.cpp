/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Container class in C++ programming language
*/

#include "container.h"

Container::Container() :
	m_spData(NULL)
{

}

Container::Container(shared_ptr<Comparable> &data) :
	m_spData(data)
{

}

Container::Container(const Container &con) :
	m_spData(con.m_spData)
{

}

Container::~Container() {
	this->m_spData.reset();
}

bool Container::operator< (const Container &c) {
	if (this->m_spData.get() == NULL || c.m_spData.get() == NULL)
		return false;

	return this->m_spData->less(*(c.m_spData));
}

bool Container::operator== (const Container &c) {
	if (this->m_spData.get() == NULL || c.m_spData.get() == NULL)
		return false;

	return this->m_spData->equal(*(c.m_spData));
}

shared_ptr<Comparable> Container::getData() const{
	return m_spData;
}

void Container::setData(shared_ptr<Comparable> &data) {
	this->m_spData = data;
}