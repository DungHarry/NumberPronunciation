/*
	Author: Dung Ly Viet
	Date created: September 14th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the ComparableImpl class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_COMPARABLE_IMPL_H_
#define _COC_COC_NUMBER_PRONUNCIATION_COMPARABLE_IMPL_H_

#include "comparable.h"
#include "base.h"

class ComparableImpl : public Base, public Comparable {
public:
	ComparableImpl();
	virtual ~ComparableImpl();

	virtual bool less(const Comparable &com);
	virtual bool equal(const Comparable &com);
};

#endif