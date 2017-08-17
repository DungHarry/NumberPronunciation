/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Container class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_CONTAINER_H_
#define _COC_COC_NUMBER_PRONUNCIATION_CONTAINER_H_

#include <memory>

using namespace std;

template <class B>
class Container : {
public:
	Container();
	Container(shared_ptr<B> &data);
	virtual ~Container();

	bool operator< (const Container<B> &c);

	shared_ptr<B>& getData();

	void setData(shared_ptr<B> &data);
private:
	shared_ptr<B> m_spData;
};

#endif