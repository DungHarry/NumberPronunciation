/*
    Author: Dung Harry
    Date created: September 5th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the StringData class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_STRING_DATA_H_
#define _COC_COC_NUMBER_PRONUNCIATION_STRING_DATA_H_

#include <memory>
#include <string>
#include "data.h"

class StringData : public Data {
public:
    StringData();
    StringData(const char *cpcValue);
    StringData(const StringData &s);
    virtual ~StringData();

    const char* getValue();
    void setValue(const char *cpcValue);
protected:
    unique_ptr<string> m_upsValue;
};

#endif
