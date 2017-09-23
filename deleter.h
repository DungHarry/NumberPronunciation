/*
    Author: Dung Harry
    Date created: September 18th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the Deleter class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_DELETER_H_
#define _COC_COC_NUMBER_PRONUNCIATION_DELETER_H_

#include "global.h"
#include "base.h"

template <class T>
class Deleter : public Base {
public:
    Deleter() :
    Base(),
    m_eType(DELETER_TYPE_NONE)
    {

    }

    Deleter(const DeleterType eType) :
    Base(),
    m_eType (eType < DELETER_TYPE_NONE || eType >= DELETER_TYPE_COUNT ? DELETER_TYPE_NONE : eType)
    {

    }

    virtual ~Deleter() {

    }

    virtual void operator()(T *pPointer) = 0;

    const DeleterType getType() {
        return this->m_eType;
    }

protected:
    DeleterType m_eType;
};

#endif
