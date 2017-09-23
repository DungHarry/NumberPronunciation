/*
    Author: Dung Harry
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Container class in C++ programming language
*/

#include "container.h"
#include "config.h"

Container::Container() :
	m_spData(nullptr)
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

bool operator< (const Container &con1, const Container &con2) {
	return (con1.m_spData.get() == nullptr || con2.m_spData.get() == nullptr) ? false : con1.m_spData->less(*(con2.m_spData.get()));
}

bool operator== (const Container &con1, const Container &con2) {
	return (con1.m_spData.get() == nullptr || con2.m_spData.get() == nullptr) ? false : con1.m_spData->equal(*(con2.m_spData.get()));
}

shared_ptr<Comparable> Container::getData() const {
	return m_spData;
}

void Container::setData(shared_ptr<Comparable> &data) {
	this->m_spData = data;
}
