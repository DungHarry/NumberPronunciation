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
