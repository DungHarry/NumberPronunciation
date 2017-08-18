/*
	Author: Dung Ly Viet
	Date created: August 18th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Language class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_LANGUAGE_H_
#define _COC_COC_NUMBER_PRONUNCIATION_LANGUAGE_H_

#include "global.h"
#include "comparable.h"
#include "base.h"
#include <string>
#include <cstring>
#include <memory>

#define LANGUAGE_TYPE_INVALID_VALUE (LANGUAGE_TYPE_NONE)
#define LANGUAGE_ID_INVALID_VALUE (static_cast<int32_t>(-1))

class Language : public Base, public Comparable {
public:
	Language();
	Language(const char *cpcName);
	virtual ~Language();
	
	const char* getName();
	void setName(const char *cpcName);

	virtual bool less(const Comparable &lang);
	virtual bool equal(const Comparable &lang);
protected:
	auto_ptr<string> m_apsName;
};

#endif