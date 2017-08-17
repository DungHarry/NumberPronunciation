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
	OBJECT_TYPE_CONFIG,
	OBJECT_TYPE_COUNT
};

enum AttributeType {
	ATTRIBUTE_TYPE_NONE = 0,
	ATTRIBUTE_TYPE_NORMAL_DIGIT,
	ATTRIBUTE_TYPE_SPECIAL_DIGIT,
	ATTRIBUTE_TYPE_CONDITION_DIGIT,
	ATTRIBUTE_TYPE_CONDITION_APPEND,
	ATTRIBUTE_TYPE_COUNT
};

enum HandlerType {};

#endif