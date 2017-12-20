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
    Date created: August 22th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the LocaleHandler class in C++ programming language
*/

#include "locale_handler.h"

template
bool LocaleHandler::setStreamLocale<wifstream>(wifstream *pStream);

template
bool LocaleHandler::setStreamLocale<wofstream>(wofstream *pStream);

unique_ptr<LocaleHandler> LocaleHandler::m_upInstance (nullptr);

LocaleHandler::LocaleHandler() :
    Handler(HANDLER_TYPE_LOCALE),
    m_upsLocaleName (new string(LOCALE_HANDLER_LOCALE_NAME_DEFAULT_VALUE)),
    m_eScope (LOCALE_HANDLER_SCOPE_ALL)
{

}

LocaleHandler::LocaleHandler(LocaleHandlerScope eScope, const char *cpcLocaleName) :
    Handler(HANDLER_TYPE_LOCALE),
    m_eScope (eScope < 0 || eScope >= LOCALE_HANDLER_SCOPE_COUNT ? LOCALE_HANDLER_SCOPE_ALL : eScope),
    m_upsLocaleName (new string(cpcLocaleName == nullptr ? LOCALE_HANDLER_LOCALE_NAME_DEFAULT_VALUE : cpcLocaleName))
{

}

LocaleHandler::~LocaleHandler() {
    m_upsLocaleName.reset();
}

bool LocaleHandler::execute() {
    if(this->m_upsLocaleName.get() == nullptr)
        return false;

    setlocale(this->m_eScope == LOCALE_HANDLER_SCOPE_ALL ? LC_ALL : (this->m_eScope == LOCALE_HANDLER_SCOPE_COLLATE ? LC_COLLATE : (this->m_eScope == LOCALE_HANDLER_SCOPE_MONETARY ? LC_MONETARY : (this->m_eScope == LOCALE_HANDLER_SCOPE_NUMERIC ? LC_NUMERIC : LC_TIME))), this->m_upsLocaleName->c_str());

    return true;
}

LocaleHandlerScope LocaleHandler::getScope() {
    return this->m_eScope;
}

void LocaleHandler::setScope(LocaleHandlerScope eScope) {
    if(eScope < 0 || eScope >= LOCALE_HANDLER_SCOPE_COUNT)
        return;

    this->m_eScope = eScope;
}

const char* LocaleHandler::getLocaleName() {
    return (this->m_upsLocaleName.get() == nullptr) ? nullptr : this->m_upsLocaleName->c_str();
}

void LocaleHandler::setLocaleName(const char *cpcLocaleName) {
    if(cpcLocaleName == nullptr)
        return;

    this->m_upsLocaleName.reset(new string(cpcLocaleName));
}

template <class T>
bool LocaleHandler::setStreamLocale(T *pStream) {
    if(pStream == nullptr || this->m_upsLocaleName.get() == nullptr)
        return false;

    pStream->imbue(locale(this->m_upsLocaleName->c_str()));

    return true;
}

LocaleHandler* LocaleHandler::getInstance() {
    if(m_upInstance.get() == nullptr)
        m_upInstance.reset(new LocaleHandler());

    return m_upInstance.get();
}
