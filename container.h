/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Container class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_CONTAINER_H_
#define _COC_COC_NUMBER_PRONUNCIATION_CONTAINER_H_

#include "comparable.h"
#include <memory>

using namespace std;

class Container {
public:
	Container();
	Container(shared_ptr<Comparable> &data);
	Container(const Container &con);
	virtual ~Container();

	bool operator< (const Container &c);
	bool operator== (const Container &c);

	shared_ptr<Comparable> getData() const;

	void setData(shared_ptr<Comparable> &data);
private:
	shared_ptr<Comparable> m_spData;
};

#endif