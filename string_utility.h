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
    Date created: August 22th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the StringUtility class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_STRING_UTILITY_H_
#define _COC_COC_NUMBER_PRONUNCIATION_STRING_UTILITY_H_

#include <memory>
#include <string>
#include <cstring>
#include <cwchar>
#include <cstdlib>
#include <iostream>
#include "utility.h"
#include "number.h"
#include "normal_digit.h"
#include "normal_digit_attribute.h"
#include "special_digit_attribute.h"
#include "config.h"

class StringUtility : public Utility {
public:
    StringUtility();
    virtual ~StringUtility();

    wchar_t* convertToWChar(const char *cpcString);
    char* convertToChar(const wchar_t *cpcString);

    wstring* convertToWString(const string *psString);
    string* convertToString(const wstring *pwsString);

    bool clearString(const char *pcString, char **pcResult);
    bool clearWString(const wchar_t *pwcString, wchar_t **pwcResult);

    bool existWChar(const wchar_t *cpwcString, const wchar_t wcCharacter);
    bool existChar(const char *cpcString, const char cCharacter);

	char* getSubStringNumber(Number *pNumber, int32_t iLength);
    char* getSubStringNumber(Number *pNumber, int32_t iStartPosition, int32_t iLength);

    char getCharacterNumber(Number *pNumber, int32_t iPosition);

    char* appendZero(const char cDigit, int32_t iCount);
    wchar_t* appendZero(const wchar_t wcDigit, int32_t iCount);

	bool isAllDigitsValid(const char *cpcString, Config *pConfig);

    bool checkSpecialCaseAndReplace(char **pcString, const char *pcSpecialString, const char *pcReplaceString);
    bool checkSpecialCaseAndReplace(wchar_t **pwcString, const wchar_t *pwcSpecialString, const wchar_t *pwcReplaceString);

    bool replaceCharacter(char *pcString, char cSource, char cTarget);
    bool replaceCharacter(wchar_t *pwcString, wchar_t wcSource, wchar_t wcTarget);

    bool eraseCharacterAtPosition(char **pcString, int32_t iPosition);
    bool eraseCharacterAtPosition(wchar_t **pwcString, int32_t iPosition);

    static StringUtility* getInstance();
private:
    static unique_ptr<StringUtility> m_upInstance;
};

#endif
