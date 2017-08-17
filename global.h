/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the global definitions in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_GLOBAL_H_
#define _COC_COC_NUMBER_PROUNICIATION_GLOBAL_H_

#include <cstdint>

enum ObjectType {
	OBJECT_TYPE_NONE = 0,
	OBJECT_TYPE_NORMAL_DIGIT,
	OBJECT_TYPE_SPECIAL_DIGIT,
	OBJECT_TYPE_PRONONCIATION_DIGIT,
	OBJECT_TYPE_PRONONCIATION_SPECIAL_DIGIT,
	OBJECT_TYPE_CONFIGURATION,
	OBJECT_TYPE_COUNT
};

#endif