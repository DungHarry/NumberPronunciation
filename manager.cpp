/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the Manager class in C++ programming language
*/

#include "manager.h"

Manager::Manager() :
	m_apObjects(new set<Container>())
{

}

Manager::~Manager() {
	if (this->m_apObjects.get() != NULL) {
		this->m_apObjects->clear();
		this->m_apObjects.reset();
	}
}

Comparable* Manager::get(const Container &con) {
	set<Container>::iterator iter;

	return (this->m_apObjects.get() == NULL || (iter = this->m_apObjects->find(con)) == this->m_apObjects->end()) ? NULL : iter->getData().get();
}

void Manager::cleanUp() {
	if (this->m_apObjects.get() != NULL) {
		this->m_apObjects->clear();
		this->m_apObjects.reset();
	}
}