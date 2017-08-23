/*
    Author: Dung Ly Viet
    Date created: August 22th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the LocaleHandler class in C++ programming language
*/

#include "locale_handler.h"

template
bool LocaleHandler::setStreamLocale<wifstream>(wifstream *pStream);

template
bool LocaleHandler::setStreamLocale<wofstream>(wofstream *pStream);

auto_ptr<LocaleHandler> LocaleHandler::m_apInstance (NULL);

LocaleHandler::LocaleHandler() :
    Handler(HANDLER_TYPE_LOCALE),
    m_apsLocaleName (new string(LOCALE_HANDLER_LOCALE_NAME_DEFAULT_VALUE)),
    m_eScope (LOCALE_HANDLER_SCOPE_ALL)
{

}

LocaleHandler::LocaleHandler(LocaleHandlerScope eScope, const char *cpcLocaleName) :
    Handler(HANDLER_TYPE_LOCALE),
    m_eScope (eScope < 0 || eScope >= LOCALE_HANDLER_SCOPE_COUNT ? LOCALE_HANDLER_SCOPE_ALL : eScope),
    m_apsLocaleName (new string(cpcLocaleName == NULL ? LOCALE_HANDLER_LOCALE_NAME_DEFAULT_VALUE : cpcLocaleName))
{

}

LocaleHandler::~LocaleHandler() {
    m_apsLocaleName.reset();
}

bool LocaleHandler::execute() {
    if(this->m_apsLocaleName.get() == NULL)
        return false;

    setlocale(this->m_eScope == LOCALE_HANDLER_SCOPE_ALL ? LC_ALL : (this->m_eScope == LOCALE_HANDLER_SCOPE_COLLATE ? LC_COLLATE : (this->m_eScope == LOCALE_HANDLER_SCOPE_MONETARY ? LC_MONETARY : (this->m_eScope == LOCALE_HANDLER_SCOPE_NUMERIC ? LC_NUMERIC : LC_TIME))), this->m_apsLocaleName->c_str());
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
    return (this->m_apsLocaleName.get() == NULL) ? NULL : this->m_apsLocaleName->c_str();
}

void LocaleHandler::setLocaleName(const char *cpcLocaleName) {
    if(cpcLocaleName == NULL)
        return;

    this->m_apsLocaleName.reset(new string(cpcLocaleName));
}

template <class T>
bool LocaleHandler::setStreamLocale(T *pStream) {
    if(pStream == NULL || this->m_apsLocaleName.get() == NULL)
        return false;

    pStream->imbue(locale(this->m_apsLocaleName->c_str()));

    return true;
}

LocaleHandler* LocaleHandler::getInstance() {
    if(m_apInstance.get() == NULL)
        m_apInstance.reset(new LocaleHandler());

    return m_apInstance.get();
}
