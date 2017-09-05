/*
	Author: Dung Ly Viet
	Date created: September 5th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the abstract class Cleanupable in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_CLEANUPABLE_H_
#define _COC_COC_NUMBER_PRONUNCIATION_CLEANUPABLE_H_

class Cleanupable {
public:
	virtual bool cleanup() = 0;
};

#endif