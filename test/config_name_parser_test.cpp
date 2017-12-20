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

    Description: this is the test source code file of the ConfigNameParser class in C++ programming language

    Compiling and running by using the following commands:
    g++ -std=c++0x -o config_name_parser_test config_name_parser_test.cpp ../config_name_parser.cpp ../file_handler.cpp ../locale_handler.cpp ../handler.cpp ../base.cpp ../string_utility.cpp ../utility.cpp ../stream_utility.cpp ../object.cpp ../config_name.cpp ../number.cpp ../normal_digit.cpp ../digit.cpp
    ./config_name_parser_test
*/

#include <iostream>
#include "../config_name_parser.h"
#include "../file_handler.h"

using namespace std;

int32_t main(int32_t argc, char **argv) {
    int32_t i;
    vector<ConfigName<wchar_t> *> *pConfigNames;

    LocaleHandler::getInstance()->setLocaleName("vi_VN");
    LocaleHandler::getInstance()->setScope(LOCALE_HANDLER_SCOPE_ALL);

    if(LocaleHandler::getInstance()->execute() == false) {
        wcout<<L"Couldn't execute the locale of vi_VN"<<endl;

        return -1;
    }

    FileHandler::getInstance()->setFileName("locales.conf");
    FileHandler::getInstance()->setType(FILE_HANDLER_TYPE_READ);

    if(FileHandler::getInstance()->execute() == false) {
        wcout<<L"Couldn't read the locales.conf file"<<endl;

        return -1;
    }

    ConfigNameParser::getInstance()->setBuffer(FileHandler::getInstance()->getBufferContent());

    if(ConfigNameParser::getInstance()->execute() == false) {
        wcout<<L"Couldn't parse the locales.conf file"<<endl;

        return -1;
    }

    if((pConfigNames = ConfigNameParser::getInstance()->releaseConfigNames()) == nullptr) {
        wcout<<L"Couldn't release the config names"<<endl;

        return -1;
    }

    for(i = 0; i < pConfigNames->size(); i ++)
        if(pConfigNames->at(i) != nullptr) {
            wcout<<L"Id: "<<(*(pConfigNames->data() + i))->getId()<<endl;
            wcout<<L"Value: "<<(*(pConfigNames->data() + i))->getValue()<<endl;
        }

    for(i = 0; i < pConfigNames->size(); i ++)
        if(*(pConfigNames->data() + i) != nullptr)
            delete *(pConfigNames->data() + i);

    pConfigNames->clear();

    delete pConfigNames;

    return 0;
}
