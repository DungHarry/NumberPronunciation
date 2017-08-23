/*
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
