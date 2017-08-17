/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Container class in C++ programming language
*/

#include "container.h"

template <class B>
Container<B>::Container() :
	m_spData(NULL)
{

}

template <class B>
Container<B>::Container(shared_ptr<B> &data) :
	m_spData(data)
{

}

template <class B>
Container<B>::~Container() {
	this->m_spData.reset();
}

template <class B>
bool Container<B>::operator< (const Container<B> &c) {
	return *(this->m_spData) < *(c.m_spData);
}

template <class B>
shared_ptr<B>& Container<B>::getData() {
	return this->m_spData;
}

template <class B>
void Container<B>::setData(shared_ptr<B> &data) {
	this->m_spData = data;
}