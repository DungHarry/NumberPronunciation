/*
    Author: Dung Harry
    Date created: September 5th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the WStringData class in C++ programming language
*/

#include "wstring_data.h"

WStringData::WStringData() :
    Data (DATA_TYPE_WSTRING),
    m_upwsValue (new wstring(L""))
{

}

WStringData::WStringData(const wchar_t *cpwcValue) :
    Data (DATA_TYPE_WSTRING),
    m_upwsValue (new wstring(cpwcValue == nullptr ? L"" : cpwcValue))
{

}

WStringData::WStringData(const WStringData &ws) :
    Data (DATA_TYPE_WSTRING),
    m_upwsValue (new wstring(ws.m_upwsValue.get() == nullptr ? L"" : ws.m_upwsValue->c_str()))
{

}

WStringData::~WStringData() {
    if(this->m_upwsValue.get() != nullptr)
        this->m_upwsValue.reset();
}

const wchar_t* WStringData::getValue() {
    return this->m_upwsValue.get() == nullptr ? nullptr : this->m_upwsValue->c_str();
}

void WStringData::setValue(const wchar_t *cpwcValue) {
    this->m_upwsValue.reset(new wstring(cpwcValue == nullptr ? L"" : cpwcValue));
}
