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
    Date created: August 23th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the test source code file of the StreamUtility class in C++ programming language

    Compiling and running by using the following commands:
    g++ -o file_handler_test file_handler_test.cpp ../file_handler.cpp ../handler.cpp ../base.cpp ../locale_handler.cpp
    ./file_handler_test
*/

#include <iostream>
#include <cstdint>
#include "../stream_utility.h"

int32_t main(int32_t argc, char **argv) {
    wchar_t *pwcLine;

    setlocale(LC_ALL, "vi_VN");

    StreamUtility::getInstance()->setContent(L"Tôi tên là Lý Việt Dũng.\nĐây là trương trình kiểm tra cho lớp StreamUtility!");

    pwcLine = StreamUtility::getInstance()->readLine();

    wcout<<"The first line is: "<< pwcLine <<endl;
    wcout<<"The next character is: "<< StreamUtility::getInstance()->readCharacter() <<endl;

    delete[] pwcLine;

    return 0;
}
