/*
    Author: Dung Ly Viet
    Date created: August 21th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the test source code file of the FileHandler class in C++ programming language

    Compiling and running by using the following commands:
    g++ -o file_handler_test file_handler_test.cpp ../file_handler.cpp ../handler.cpp ../base.cpp ../locale_handler.cpp
    ./file_handler_test
*/

#include <iostream>
#include "../file_handler.h"

int32_t main(int32_t argc, char **argv) {
    LocaleHandler::getInstance()->setLocaleName("vi_VN");
    LocaleHandler::getInstance()->setScope(LOCALE_HANDLER_SCOPE_ALL);

    LocaleHandler::getInstance()->execute();

    FileHandler::getInstance()->setFileName("file_handler_test.cpp");
    FileHandler::getInstance()->setType(FILE_HANDLER_TYPE_READ);

    if(FileHandler::getInstance()->execute() == true) {
        wcout<<"Reading from file_handler_test.cpp successfully"<<endl;
        wcout<<"The content of file: "<<endl<<endl;

        wcout<<(FileHandler::getInstance()->getBufferContent() == NULL ? L"NULL" : FileHandler::getInstance()->getBufferContent())<<endl;

        FileHandler::getInstance()->setFileName("file_handler_test.txt");
        FileHandler::getInstance()->setType(FILE_HANDLER_TYPE_WRITE);

        if(FileHandler::getInstance()->execute() == true)
            wcout<<"Writing to file_handler_test.txt successfully"<<endl;
        else
            wcout<<"Writing to file_handler_test.txt failurelly"<<endl;
    } else
        wcout<<"Reading from file_handler_test.cpp failurelly"<<endl;

    return 0;
}
