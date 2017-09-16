/*
    Author: Dung Ly Viet
    Date created: August 21th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the FileHandler class in C++ programming language
*/

#include <iostream>
#include "file_handler.h"

unique_ptr<FileHandler> FileHandler::m_upInstance(nullptr);

FileHandler::FileHandler() :
    Handler(HANDLER_TYPE_FILE),
    m_upsBuffer (new wstring()),
    m_upsFileName (new string()),
    m_eType (FILE_HANDLER_TYPE_NONE)
{

}

FileHandler::~FileHandler() {
    if(this->m_upsBuffer.get() != nullptr)
        this->m_upsBuffer.reset();

    if(this->m_upsFileName.get() != nullptr)
        this->m_upsFileName.reset();
}

bool FileHandler::execute() {
    return (this->m_eType == FILE_HANDLER_TYPE_READ) ? this->read() : (this->m_eType == FILE_HANDLER_TYPE_WRITE ? this->write() : false);
}

FileHandler* FileHandler::getInstance() {
    if(m_upInstance.get() == nullptr)
        m_upInstance.reset(new FileHandler());

    return m_upInstance.get();
}

bool FileHandler::read() {
    unique_ptr<wifstream> apfFile(nullptr);
    wchar_t* pcTmpBuffer = nullptr;
    int32_t iFileSize;

    if(this->m_eType != FILE_HANDLER_TYPE_READ || this->m_upsFileName.get() == nullptr)
        return false;
    apfFile.reset(new wifstream(this->m_upsFileName->c_str()));

    if(apfFile.get() == nullptr || apfFile->is_open() == false)
        return false;

    LocaleHandler::getInstance()->setStreamLocale<wifstream>(apfFile.get());
    iFileSize = this->getFileSize(apfFile.get());

    if(iFileSize <= 0) {
        apfFile->close();

        return false;
    }

    pcTmpBuffer = new wchar_t[iFileSize + 1];

    apfFile->read(pcTmpBuffer, iFileSize);

    this->m_upsBuffer.reset(new wstring(pcTmpBuffer));

    apfFile->close();

    delete[] pcTmpBuffer;

    return true;
}

bool FileHandler::write() {
    unique_ptr<wofstream> apfFile(nullptr);

    if(this->m_eType != FILE_HANDLER_TYPE_WRITE || this->m_upsFileName.get() == nullptr)
        return false;

    apfFile.reset(new wofstream(this->m_upsFileName->c_str()));

    if(apfFile.get() == nullptr || apfFile->is_open() == false)
        return false;

    LocaleHandler::getInstance()->setStreamLocale<wofstream>(apfFile.get());
    apfFile->write(this->m_upsBuffer->c_str(), this->m_upsBuffer->size());

    apfFile->close();

    return true;
}

const wchar_t* FileHandler::getBufferContent() {
    return (this->m_upsBuffer.get() == nullptr) ? nullptr : this->m_upsBuffer->c_str();
}

int32_t FileHandler::getFileSize(wifstream *pInputFileStream) {
    int32_t iCurrentPosition, iFileSize;

    if(pInputFileStream == nullptr || pInputFileStream->is_open() == false)
        return -1;

    iCurrentPosition = static_cast<int32_t>(pInputFileStream->tellg());

    pInputFileStream->clear();
    pInputFileStream->seekg(0, pInputFileStream->end);

    iFileSize = static_cast<int32_t>(pInputFileStream->tellg());

    pInputFileStream->clear();
    pInputFileStream->seekg(iCurrentPosition, pInputFileStream->beg);

    return iFileSize;
}

FileHandlerType FileHandler::getType() {
    return this->m_eType;
}

void FileHandler::setType(FileHandlerType eType) {
    if(eType < FILE_HANDLER_TYPE_NONE || eType >= FILE_HANDLER_TYPE_COUNT)
        return;

    this->m_eType = eType;
}

const char *FileHandler::getFileName() {
    return (this->m_upsFileName.get() == nullptr) ? nullptr : this->m_upsFileName->c_str();
}

void FileHandler::setFileName(const char *cpcFileName) {
    if(cpcFileName == nullptr)
        return;

    this->m_upsFileName.reset(new string(cpcFileName));
}
