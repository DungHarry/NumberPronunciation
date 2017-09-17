/*
    Author: Dung Ly Viet
    Date created: September 18th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the NullDeleter class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_NULL_DELETER_H_
#define _COC_COC_NUMBER_PRONUNCIATION_NULL_DELETER_H_

#include "deleter.h"

template <class T>
class NullDeleter : public Deleter<T> {
public:
    NullDeleter() :
    Deleter<T>(DELETER_TYPE_NULL)
    {

    }

    virtual ~NullDeleter() {

    }

    virtual void operator()(T *pPointer) {

    }
};

#endif
