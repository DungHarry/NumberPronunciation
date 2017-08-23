/*
    Author: Dung Ly Viet
    Date created: August 21th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the FileHandler class in C++ programming language
*/

#include "file_handler.h"

auto_ptr<FileHandler> FileHandler::m_apInstance(NULL);

FileHandler::FileHandler() :
    Handler(HANDLER_TYPE_FILE),
    m_apsBuffer (new wstring()),
    m_apsFileName (new string()),
    m_eType (FILE_HANDLER_TYPE_NONE)
{

}

FileHandler::~FileHandler() {
    if(this->m_apsBuffer.get() != NULL)
        this->m_apsBuffer.reset();

    if(this->m_apsFileName.get() != NULL)
        this->m_apsFileName.reset();
}

bool FileHandler::execute() {
    return (this->m_eType == FILE_HANDLER_TYPE_READ) ? this->read() : (this->m_eType == FILE_HANDLER_TYPE_WRITE ? this->write() : false);
}

FileHandler* FileHandler::getInstance() {
    if(m_apInstance.get() == NULL)
        m_apInstance.reset(new FileHandler());

    return m_apInstance.get();
}

bool FileHandler::read() {
    auto_ptr<wifstream> apfFile(NULL);
    wchar_t* pcTmpBuffer = NULL;
    int32_t iFileSize;

    if(this->m_eType != FILE_HANDLER_TYPE_READ || this->m_apsFileName.get() == NULL)
        return false;

    apfFile.reset(new wifstream(this->m_apsFileName->c_str()));

    if(apfFile.get() == NULL || apfFile->is_open() == false)
        return false;

    LocaleHandler::getInstance()->setStreamLocale<wifstream>(apfFile.get());
    iFileSize = this->getFileSize(apfFile.get());

    if(iFileSize <= 0) {
        apfFile->close();

        return false;
    }

    pcTmpBuffer = new wchar_t[iFileSize + 1];

    apfFile->read(pcTmpBuffer, iFileSize);

    this->m_apsBuffer->assign(pcTmpBuffer);

    apfFile->close();

    delete[] pcTmpBuffer;

    return true;
}

bool FileHandler::write() {
    auto_ptr<wofstream> apfFile(NULL);

    if(this->m_eType != FILE_HANDLER_TYPE_WRITE || this->m_apsFileName.get() == NULL)
        return false;

    apfFile.reset(new wofstream(this->m_apsFileName->c_str()));

    if(apfFile.get() == NULL || apfFile->is_open() == false)
        return false;

    LocaleHandler::getInstance()->setStreamLocale<wofstream>(apfFile.get());
    apfFile->write(this->m_apsBuffer->c_str(), this->m_apsBuffer->size());

    apfFile->close();

    return true;
}

const wchar_t* FileHandler::getBufferContent() {
    return (this->m_apsBuffer.get() == NULL) ? NULL : this->m_apsBuffer->c_str();
}

int32_t FileHandler::getFileSize(wifstream *pInputFileStream) {
    int32_t iCurrentPosition, iFileSize;

    if(pInputFileStream == NULL || pInputFileStream->is_open() == false)
        return -1;

    iCurrentPosition = pInputFileStream->tellg();

    pInputFileStream->clear();
    pInputFileStream->seekg(0, pInputFileStream->end);

    iFileSize = pInputFileStream->tellg();

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
    return (this->m_apsFileName.get() == NULL) ? NULL : this->m_apsFileName->c_str();
}

void FileHandler::setFileName(const char *cpcFileName) {
    if(cpcFileName == NULL)
        return;

    this->m_apsFileName.reset(new string(cpcFileName));
}
