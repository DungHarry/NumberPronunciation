/*
    NumberPronunciation provides a way to pronounce a number
    Copyright (C) 2017 of Dung Harry

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.

    Author: Dung Harry
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

bool StandardIOUtility::write(const char *pcContent) {
	if (pcContent == nullptr)
		return false;

	cout << pcContent ;

	return true;
}

bool StandardIOUtility::write(const wchar_t *pwcContent) {
	if (pwcContent == nullptr)
		return false;

	wcout << pwcContent ;

	return true;
}
bool StandardIOUtility::writeLine(const char *pcContent) {
	if (pcContent == nullptr)
		return false;

	cout << pcContent <<endl;

	return true;
}

bool StandardIOUtility::writeLine(const wchar_t *pwcContent) {
	if (pwcContent == nullptr)
		return false;

	wcout << pwcContent <<endl;

	return true;
}


StandardIOUtility* StandardIOUtility::getInstance() {
	if (m_upInstance.get() == nullptr)
		m_upInstance.reset(new StandardIOUtility());

	return m_upInstance.get();
}
