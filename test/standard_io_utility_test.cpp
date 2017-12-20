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
