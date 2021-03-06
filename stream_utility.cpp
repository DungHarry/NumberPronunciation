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
    Date created: August 23th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the StreamUtility class in C++ programming language
*/

#include "stream_utility.h"

unique_ptr<StreamUtility> StreamUtility::m_upInstance (nullptr);

StreamUtility::StreamUtility() :
    Utility (UTILITY_TYPE_STREAM),
    m_upStream (new wstringstream())
{

}

StreamUtility::StreamUtility(const wchar_t *pwcContent) :
    Utility (UTILITY_TYPE_STREAM),
    m_upStream (new wstringstream(wstring(pwcContent)))
{

}

StreamUtility::~StreamUtility() {
    if(this->m_upStream.get() != nullptr) {
        this->m_upStream->clear();

        this->m_upStream.reset();
    }
}

wchar_t* StreamUtility::readLine() {
    vector<wchar_t> *pLine;
    wchar_t *pwcResult;
    wchar_t c;

    if(this->m_upStream.get() == nullptr || this->m_upStream->str().size() <= 0)
        return nullptr;

    pLine = new vector<wchar_t>();

    while(this->m_upStream->eof() == false && (c = this->m_upStream->get()) != '\n')
        pLine->push_back(c);

    pLine->push_back(L'\0');

    pwcResult = new wchar_t[pLine->size()];

    wcscpy(pwcResult, pLine->data());

    pLine->clear();

    delete pLine;

    return pwcResult;
}

wchar_t StreamUtility::readCharacter() {
    return (this->m_upStream.get() == nullptr) ? WEOF : this->m_upStream->get();
}

bool StreamUtility::isEndOfStream() {
    return (this->m_upStream.get() == nullptr) ? true : this->m_upStream->eof();
}

bool StreamUtility::setContent(const wchar_t *pwcContent) {
    if(pwcContent == nullptr)
        return false;

    this->m_upStream.reset(new wstringstream(wstring(pwcContent)));

    return true;
}

bool StreamUtility::clearContent() {
    if(this->m_upStream.get() == nullptr)
        return false;

    this->m_upStream.reset(new wstringstream(wstring(L"")));

    return true;
}

StreamUtility* StreamUtility::getInstance() {
    if(m_upInstance.get() == nullptr)
        m_upInstance.reset(new StreamUtility());

    return m_upInstance.get();
}
