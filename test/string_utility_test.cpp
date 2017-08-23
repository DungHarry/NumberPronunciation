/*
    Author: Dung Ly Viet
    Date created: August 22th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the test source code file of the StringUtility class in C++ programming language

    Compile and run by using the following commands:
    g++ -o string_utility_test string_utility_test.cpp ../string_utility.cpp ../utility.cpp ../base.cpp
    ./string_utility_test
*/

#include "../string_utility.h"
#include <iostream>
#include <cstdio>
#include <cstdint>

int32_t main(int32_t argc, char **argv) {
    char *pcString;
    wchar_t *pwcString;
    string *psString;
    wstring *pwsString;

    pwcString = StringUtility::getInstance()->convertToWChar("I am Dung Harry!");

    wcout<<"Result of convertToWChar: "<< (pwcString) <<endl;

    pcString = StringUtility::getInstance()->convertToChar(pwcString);

    if(pcString == NULL)
        wcout<<"Fail to do convertToChar"<<endl;
    else
        wcout<<"Result of convertToChar: "<< pcString <<endl;

    psString = new string("This is the test of StringUtility!");

    pwsString = StringUtility::getInstance()->convertToWString(psString);

    delete psString;

    wcout<<"Result of convertToWString: "<< (pwsString->c_str()) <<endl;

    psString = StringUtility::getInstance()->convertToString(pwsString);

    if(psString == NULL)
        wcout<<"Fail to do convertToString"<<endl;
    else
        wcout<<"Result of convertToString: "<< psString->c_str() <<endl;

    if(pwsString != NULL)
        delete pwsString;

    if(psString != NULL)
        delete psString;

    if(pwcString != NULL)
        delete[] pwcString;

    if(pcString != NULL)
        delete[] pcString;

    return 0;
}
