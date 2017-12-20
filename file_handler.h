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

    Author: Dung Harry
    Date created: August 21th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the FileHandler class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_FILE_HANDLER_H_
#define _COC_COC_NUMBER_PRONUNCIATION_FILE_HANDLER_H_

#include "handler.h"
#include "locale_handler.h"
#include <fstream>
#include <string>
#include <memory>

using namespace std;

enum FileHandlerType {
    FILE_HANDLER_TYPE_NONE = 0,
    FILE_HANDLER_TYPE_READ,
    FILE_HANDLER_TYPE_WRITE,
    FILE_HANDLER_TYPE_COUNT
};

class FileHandler : public Handler {
public:
    FileHandler();
    virtual ~FileHandler();

    virtual bool execute();

    FileHandlerType getType();
    void setType(FileHandlerType eType);

    const char* getFileName();
    void setFileName(const char *cpcFileName);

    static FileHandler* getInstance();

    const wchar_t* getBufferContent();
protected:
    bool read();
    bool write();

    FileHandlerType m_eType;
    unique_ptr<string> m_upsFileName;
    unique_ptr<wstring> m_upsBuffer;
private:
    int32_t getFileSize(wifstream *pInputFileStream);

    static unique_ptr<FileHandler> m_upInstance;
};

#endif
