/*
    NumberPronunciation provides a way to pronounce a number
    Copyright (C) 2017 of Dung Harry

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.

    Author: Dung Harry
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
