/*
    Author: Dung Ly Viet
    Date created: August 22th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the test source code file of the StringUtility class in C++ programming language

    Compile and run by using the following commands:
    On Linux:
	
	g++ -o string_utility_test string_utility_test.cpp ../string_utility.cpp ../utility.cpp ../base.cpp
    ./string_utility_test

	On Windows:
	cl /W4 string_utility_test.cpp ../string_utility.cpp ../utility.cpp ../base.cpp
	string_utility_test.exe
*/

#include "../string_utility.h"
#include <iostream>
#include <cstdio>
#include <cstdint>
#include <locale>
#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

int32_t main(int32_t argc, char **argv) {
    char *pcString, *pcResult;
    wchar_t *pwcString, *pwcResult;
    string *psString;
    wstring *pwsString;

#ifdef _WIN32
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	setlocale(LC_ALL, "vi_VN");

    pwcString = StringUtility::getInstance()->convertToWChar("I am Dung Harry!");

    wcout<<L"Result of convertToWChar: "<< (pwcString) <<endl;

    pcString = StringUtility::getInstance()->convertToChar(pwcString);

    if(pcString == NULL)
        wcout<<L"Fail to do convertToChar"<<endl;
    else
        wcout<<L"Result of convertToChar: "<< pcString <<endl;

    psString = new string("This is the test of StringUtility!");

    pwsString = StringUtility::getInstance()->convertToWString(psString);

    delete psString;

    wcout<<L"Result of convertToWString: "<< (pwsString->c_str()) <<endl;

    psString = StringUtility::getInstance()->convertToString(pwsString);

    if(psString == NULL)
        wcout<<L"Fail to do convertToString"<<endl;
    else
        wcout<<L"Result of convertToString: "<< psString->c_str() <<endl;

    if(pwsString != NULL)
        delete pwsString;

    if(psString != NULL)
        delete psString;

    if(pwcString != NULL)
        delete[] pwcString;

    if(pcString != NULL)
        delete[] pcString;

	psString = new string("    1 10 . point //Configuration of dot digit in Vietnamese pronunciation ");

	pcResult = NULL;

	if(StringUtility::getInstance()->clearString(psString->c_str(), &pcResult) == true) {
		wcout<<L"The clean string is: "<< pcResult <<endl;

		delete[] pcResult;
	} else 
		wcout<<L"Couldn't clear the string"<<endl;

	pwsString = new wstring(L"    1 10 . chấm //Configuration of dot digit in Vietnamese pronunciation ");

	pwcResult = NULL;

	if (StringUtility::getInstance()->clearWString(pwsString->c_str(), &pwcResult) == true) {
		wcout<<L"The clean wide string is: "<< pwcResult <<endl;

		delete[] pwcResult;
	} else
		wcout<<L"Couldn't clear the wide string"<<endl;

	if(psString != NULL)
		delete psString;

	if (pwsString != NULL)
		delete pwsString;

    return 0;
}
