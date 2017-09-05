/*
	Author: Dung Ly Viet
	Date created: September 5th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the StandardIOUtility class in C++ programming language
*/

#include "standard_io_utility.h"

unique_ptr<StandardIOUtility> StandardIOUtility::m_upInstance (nullptr);

StandardIOUtility::StandardIOUtility() :
	Utility (UTILITY_TYPE_STANDARD_IO)
{

}

StandardIOUtility::~StandardIOUtility() {

}

bool StandardIOUtility::readLine(char *pcBuffer, int32_t iBufferSize) {
	int32_t i;
	
	if (pcBuffer == nullptr || iBufferSize <= 0)
		return false;

	for (i = 0; i < iBufferSize - 1 && (*(pcBuffer + i) = getc(stdin)) != '\n'; i ++);

	*(pcBuffer + i) = '\0';

	return true;
}

bool StandardIOUtility::readLine(wchar_t *pwcBuffer, int32_t iBufferSize) {
	int32_t i;

	if (pwcBuffer == nullptr || iBufferSize <= 0)
		return false;

	for (i = 0; i < iBufferSize - 1 && (*(pwcBuffer + i) = getwc(stdin)) != L'\n'; i ++);

	*(pwcBuffer + i) = L'\0';

	return true;
}

StandardIOUtility* StandardIOUtility::getInstance() {
	if (m_upInstance.get() == nullptr)
		m_upInstance.reset(new StandardIOUtility());

	return m_upInstance.get();
}