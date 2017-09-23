/*
    Author: Dung Harry
    Date created: September 3rd, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the ConfigNameParser class in C++ programming language
*/

#include "config_name_parser.h"

unique_ptr<ConfigNameParser> ConfigNameParser::m_upInstance (nullptr);

ConfigNameParser::ConfigNameParser() :
    Handler (HANDLER_TYPE_CONFIG_NAME_PARSE),
    m_upConfigNames (nullptr),
    m_upwsBuffer (nullptr)
{

}

ConfigNameParser::ConfigNameParser(const wchar_t *cpwcBuffer) :
    Handler (HANDLER_TYPE_CONFIG_NAME_PARSE),
    m_upConfigNames (nullptr),
    m_upwsBuffer (cpwcBuffer == nullptr ? nullptr : new wstring(cpwcBuffer))
{

}

ConfigNameParser::~ConfigNameParser() {
    int32_t i;

    if(this->m_upConfigNames.get() != nullptr) {
        for(i = 0; i < this->m_upConfigNames->size(); i ++)
            if(this->m_upConfigNames->at(i) != nullptr)
                delete this->m_upConfigNames->at(i);

        this->m_upConfigNames->clear();

        this->m_upConfigNames.reset();
    }

    if(this->m_upwsBuffer.get() != nullptr)
        this->m_upwsBuffer.reset();
}

bool ConfigNameParser::execute() {
    wchar_t *pwcLine, *pwcCleanLine;
    int32_t i;

    if(this->m_upwsBuffer.get() == nullptr)
        return false;

    if(this->m_upConfigNames.get() != nullptr) {
        for(i = 0; i < this->m_upConfigNames->size(); i ++)
            if(*(this->m_upConfigNames->data() + i) != nullptr)
                delete *(this->m_upConfigNames->data() + i);

        this->m_upConfigNames->clear();

        this->m_upConfigNames.reset();
    }

    this->m_upConfigNames.reset(new vector<ConfigName<wchar_t> *>());

    StreamUtility::getInstance()->setContent(this->m_upwsBuffer->c_str());

    for(pwcLine = nullptr; StreamUtility::getInstance()->isEndOfStream() == false; ) {
        if((pwcLine = StreamUtility::getInstance()->readLine()) == nullptr || wcslen(pwcLine) <= 0) {
            if(pwcLine != nullptr)
                delete[] pwcLine;

            continue;
        }

        pwcCleanLine = nullptr;

        if(StringUtility::getInstance()->clearWString(pwcLine, &pwcCleanLine) == false || pwcCleanLine == nullptr) {
            delete[] pwcLine;

            if(pwcCleanLine != nullptr)
                delete[] pwcCleanLine;

            continue;
        }

        this->parseLine(pwcCleanLine);

        delete[] pwcCleanLine;
        delete[] pwcLine;
    }

    return true;
}

vector<ConfigName<wchar_t> *>* ConfigNameParser::releaseConfigNames() {
    return this->m_upConfigNames.release();
}

const wchar_t *ConfigNameParser::getBuffer() {
    return this->m_upwsBuffer.get() == nullptr ? nullptr : this->m_upwsBuffer->c_str();
}

void ConfigNameParser::setBuffer(const wchar_t *cpwcBuffer) {
    if(cpwcBuffer == nullptr)
        return;

    this->m_upwsBuffer.reset(new wstring(cpwcBuffer));
}

ConfigNameParser* ConfigNameParser::getInstance() {
    if(m_upInstance.get() == nullptr)
        m_upInstance.reset(new ConfigNameParser());

    return m_upInstance.get();
}

bool ConfigNameParser::parseLine(const wchar_t *cpwcLine) {
    wchar_t *pwcBuffer;
    int32_t iId;

    if(cpwcLine == nullptr || this->m_upConfigNames.get() == nullptr)
        return false;

    pwcBuffer = new wchar_t[CONFIG_NAME_PARSER_BUFFER_LENGTH];

    if(swscanf(cpwcLine, L"%d %ls", &iId, pwcBuffer) != 2) {
        delete[] pwcBuffer;

        return false;
    }

    this->m_upConfigNames->push_back(new ConfigName<wchar_t>(static_cast<int16_t>(iId), pwcBuffer));

    delete[] pwcBuffer;

    return true;
}
