/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Manager class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_MANAGER_H_
#define _COC_COC_NUMBER_PRONUNCIATION_MANAGER_H_

#include <set>
#include <memory>
#include "container.h"

class Manager {
public:
    typedef set<Container>::iterator iterator;
    typedef set<Container>::reverse_iterator reverse_iterator;

	Manager();
	virtual ~Manager();

    set<Container>* getObjects();

	Comparable* get(const Container &con);

	void cleanUp();

    iterator begin();
    iterator end();

    reverse_iterator rbegin();
    reverse_iterator rend();
protected:
	unique_ptr<set<Container>> m_upObjects;
};

class ManagerDeleter {
public:
	void operator() (Manager *pManager);
};

#endif
