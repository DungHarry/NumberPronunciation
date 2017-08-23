/*
    Author: Dung Ly Viet
    Date created: August 22th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the LocaleHandler class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_LOCALE_HANDLER_H_
#define _COC_COC_NUMBER_PRONUNCIATION_LOCALE_HANDLER_H_

#include "handler.h"
#include <locale>
#include <memory>
#include <fstream>

using namespace std;

enum LocaleHandlerScope {
    LOCALE_HANDLER_SCOPE_ALL = 0,
    LOCALE_HANDLER_SCOPE_COLLATE,
    LOCALE_HANDLER_SCOPE_MONETARY,
    LOCALE_HANDLER_SCOPE_NUMERIC,
    LOCALE_HANDLER_SCOPE_TIME,
    LOCALE_HANDLER_SCOPE_COUNT
};

#define LOCALE_HANDLER_LOCALE_NAME_DEFAULT_VALUE ("en_US")

class LocaleHandler : public Handler {
public:
    LocaleHandler();
    LocaleHandler(LocaleHandlerScope eScope, const char *cpcLocaleName);
    virtual ~LocaleHandler();

    virtual bool execute();

    LocaleHandlerScope getScope();
    void setScope(LocaleHandlerScope eScope);

    const char* getLocaleName();
    void setLocaleName(const char *cpcLocaleName);

    template <class T>
    bool setStreamLocale(T *pStream); /*{
        if(pStream == NULL || this->m_apsLocaleName.get() == NULL)
            return false;

        pStream->imbue(locale(this->m_apsLocaleName->c_str()));

        return true;
    }*/

    static LocaleHandler* getInstance();
protected:
    LocaleHandlerScope m_eScope;
    auto_ptr<string> m_apsLocaleName;
private:
    static auto_ptr<LocaleHandler> m_apInstance;
};

extern template
bool LocaleHandler::setStreamLocale<wifstream>(wifstream *pStream);

extern template
bool LocaleHandler::setStreamLocale<wofstream>(wofstream *pStream);

#endif
