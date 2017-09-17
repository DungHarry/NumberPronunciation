/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the Manager class in C++ programming language
*/

#include "manager.h"

Manager::Manager() :
	m_upObjects(new set<Container>())
{

}

Manager::~Manager() {
	if (this->m_upObjects.get() != nullptr) {
		this->m_upObjects->clear();
		this->m_upObjects.reset();
	}
}

set<Container>* Manager::getObjects() {
    return this->m_upObjects.get();
}

Comparable* Manager::get(const Container &con) {
	set<Container>::iterator iter;

	return (this->m_upObjects.get() == nullptr || (iter = this->m_upObjects->find(con)) == this->m_upObjects->end()) ? nullptr : iter->getData().get();
}

void Manager::cleanUp() {
	if (this->m_upObjects.get() != nullptr) {
		this->m_upObjects->clear();
		this->m_upObjects.reset();
	}
}

Manager::iterator Manager::begin() {
    return this->m_upObjects->begin();
}

Manager::iterator Manager::end() {
    return this->m_upObjects->end();
}

Manager::reverse_iterator Manager::rbegin() {
    return this->m_upObjects->rbegin();
}

Manager::reverse_iterator Manager::rend() {
    return this->m_upObjects->rend();
}

void ManagerDeleter::operator() (Manager *pManager) {
	if (pManager == nullptr)
		return;

    delete pManager;
    pManager = nullptr;
}
