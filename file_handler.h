/*
    Author: Dung Ly Viet
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
    auto_ptr<string> m_apsFileName;
    auto_ptr<wstring> m_apsBuffer;
private:
    int32_t getFileSize(wifstream *pInputFileStream);

    static auto_ptr<FileHandler> m_apInstance;
};

#endif
