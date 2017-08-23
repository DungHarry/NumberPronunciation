/*
    Author: Dung Ly Viet
    Date created: August 22th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the StringUtility class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_STRING_UTILITY_H_
#define _COC_COC_NUMBER_PRONUNCIATION_STRING_UTILITY_H_

#include "utility.h"
#include <memory>
#include <string>
#include <cstring>
#include <cwchar>
#include <cstdlib>
#include <iostream>

class StringUtility : public Utility {
public:
    StringUtility();
    virtual ~StringUtility();

    wchar_t* convertToWChar(const char *cpcString);
    char* convertToChar(const wchar_t *cpcString);

    wstring* convertToWString(const string *psString);
    string* convertToString(const wstring *pwsString);

    bool clearString(const char *pcString, wchar_t **pcResult);
    bool clearWString(const wchar_t *pwcString, wchar_t **pwcResult);

    bool existWChar(const wchar_t *cpwcString, const wchar_t wcCharacter);
    bool existChar(const char *cpcString, const char cCharacter);

    static StringUtility* getInstance();
private:
    static auto_ptr<StringUtility> m_apInstance;
};

#endif
