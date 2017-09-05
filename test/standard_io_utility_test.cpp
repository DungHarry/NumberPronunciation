/*
	Author: Dung Ly Viet
	Date created: September 5th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the test source code file of the StandardIOUtility class in C++ programming language

	Compile and run by using the following commands:
	g++ -std=c++0x -o standard_io_utility_test.exe standard_io_utility_test.cpp ../standard_io_utility.cpp ../utility.cpp ../base.cpp
	standard_io_utility_test.exe
*/

#include "../standard_io_utility.h"

int32_t main(int32_t argc, char **argv) {
	char *pcBuffer = new char[1 << 10];
	wchar_t *pwcBuffer = new wchar_t[1 << 10];

	StandardIOUtility::getInstance()->readLine(pcBuffer, 1 << 10);

	cout << "The read line: " << pcBuffer << endl;

	StandardIOUtility::getInstance()->readLine(pwcBuffer, 1 << 10);

	wcout << L"The read line: " << pwcBuffer << endl;

	delete[] pcBuffer;
	delete[] pwcBuffer;

	return 0;
}