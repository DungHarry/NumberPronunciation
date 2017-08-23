/*
    Author: Dung Ly Viet
    Date created: August 23th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the StreamUtility class in C++ programming language
*/

#include "stream_utility.h"

auto_ptr<StreamUtility> StreamUtility::m_apInstance (NULL);

StreamUtility::StreamUtility() :
    Utility (UTILITY_TYPE_STREAM),
    m_apStream (new wstringstream())
{

}

StreamUtility::StreamUtility(const wchar_t *pwcContent) :
    Utility (UTILITY_TYPE_STREAM),
    m_apStream (new wstringstream(wstring(pwcContent)))
{

}

StreamUtility::~StreamUtility() {
    if(this->m_apStream.get() != NULL) {
        this->m_apStream->clear();

        this->m_apStream.reset();
    }
}

wchar_t* StreamUtility::readLine() {
    vector<wchar_t> *pLine;
    wchar_t *pwcResult;
    wchar_t c;

    if(this->m_apStream.get() == NULL || this->m_apStream->str().size() <= 0)
        return NULL;

    pLine = new vector<wchar_t>();

    while(this->m_apStream->eof() == false && (c = this->m_apStream->get()) != '\n')
        pLine->push_back(c);

    pLine->push_back(L'\0');

    pwcResult = new wchar_t[pLine->size()];

    wcscpy(pwcResult, pLine->data());

    pLine->clear();

    delete pLine;

    return pwcResult;
}

wchar_t StreamUtility::readCharacter() {
    return (this->m_apStream.get() == NULL) ? WEOF : this->m_apStream->get();
}

bool StreamUtility::isEndOfStream() {
    return (this->m_apStream.get() == NULL) ? false : this->m_apStream->eof();
}

bool StreamUtility::setContent(const wchar_t *pwcContent) {
    if(this->m_apStream.get() == NULL || pwcContent == NULL)
        return false;

    this->m_apStream->str(wstring(pwcContent));

    return true;
}

bool StreamUtility::clearContent() {
    if(this->m_apStream.get() == NULL)
        return false;

    this->m_apStream->str(wstring(L""));

    return true;
}

StreamUtility* StreamUtility::getInstance() {
    if(m_apInstance.get() == NULL)
        m_apInstance.reset(new StreamUtility());

    return m_apInstance.get();
}
