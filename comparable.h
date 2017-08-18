/*
	Author: Dung Ly Viet
	Date created: August 18th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Comparable abstract class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_COMPARABLE_H_
#define _COC_COC_NUMBER_PRONUNCIATION_COMPARABLE_H_

using namespace std;

class Comparable {
public:
	virtual bool less(const Comparable &com) = 0;
	virtual bool equal(const Comparable &com) = 0;
};

#endif