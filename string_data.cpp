/*
    Author: Dung Harry
    Date created: September 5th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the StringData class in C++ programming language
*/

#include "string_data.h"

StringData::StringData() :
    Data (DATA_TYPE_STRING),
    m_upsValue (new string(""))
{

}
StringData::StringData(const char *cpcValue) :
    Data (DATA_TYPE_STRING),
    m_upsValue (new string(cpcValue == nullptr ? "" : cpcValue))
{

}

StringData::StringData(const StringData &s) :
    Data(DATA_TYPE_STRING),
    m_upsValue (new string(s.m_upsValue.get() == nullptr ? "" : s.m_upsValue->c_str()))
{

}

StringData::~StringData() {
    if(this->m_upsValue.get() != nullptr)
        this->m_upsValue.reset();
}

const char* StringData::getValue() {
    return this->m_upsValue.get() == nullptr ? nullptr : this->m_upsValue->c_str();
}

void StringData::setValue(const char *cpcValue) {
    this->m_upsValue.reset(new string(cpcValue == nullptr ? "" : cpcValue));
}
