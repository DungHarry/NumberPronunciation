/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Manager class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_MANAGER_H_
#define _COC_COC_NUMBER_PRONUNCIATION_MANAGER_H_

#include "container.h"
#include <set>
#include <memory>

class Manager {
public:
	Manager();
	virtual ~Manager();

	Comparable* get(const Container &con);

	void cleanUp();
private:
	auto_ptr<set<Container>> m_apObjects;
};

#endif