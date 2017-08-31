/*
    Author: Dung Ly Viet
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

    static StringUtility* getInstance();
private:
    static unique_ptr<StringUtility> m_upInstance;
};

#endif
