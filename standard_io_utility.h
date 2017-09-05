/*
	Author: Dung Ly Viet
	Date created: September 5th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the StandardIOUtility class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_STANDARD_IO_UTILITY_H_
#define _COC_COC_NUMBER_PRONUNCIATION_STANDARD_IO_UTILITY_H_

#include <iostream>
#include <string>
#include <memory>
#include <cstdint>
#include "utility.h"

class StandardIOUtility : public Utility {
public:
	StandardIOUtility();
	virtual ~StandardIOUtility();

	bool readLine(char *pcBuffer, int32_t iBufferSize);
	bool readLine(wchar_t *pwcBuffer, int32_t iBufferSize);

	static StandardIOUtility* getInstance();
private:
	static unique_ptr<StandardIOUtility> m_upInstance;
};

#endif