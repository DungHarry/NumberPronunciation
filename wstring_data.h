/*
    Author: Dung Ly Viet
    Date created: September 5th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the WStringData class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_WSTRING_DATA_H_
#define _COC_COC_NUMBER_PRONUNCIATION_WSTRING_DATA_H_

#include <memory>
#include <string>
#include "data.h"

class WStringData : public Data {
public:
    WStringData();
    WStringData(const wchar_t *cpwcValue);
    WStringData(const WStringData &ws);
    virtual ~WStringData();

    const wchar_t* getValue();
    void setValue(const wchar_t *cpwcValue);
protected:
    unique_ptr<wstring> m_upwsValue;
};

#endif
