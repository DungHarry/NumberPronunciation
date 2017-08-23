/*
    Author: Dung Ly Viet
    Date created: August 22th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the Utility class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_UTILITY_H_
#define _COC_COC_NUMBER_PRONUNCIATION_UTILITY_H_

#include "global.h"
#include "base.h"

class Utility : public Base {
public:
    Utility();
    Utility(UtilityType eType);
    virtual ~Utility();

    UtilityType getType();
    void setType(UtilityType eType);
protected:
    UtilityType m_eType;
};

#endif
