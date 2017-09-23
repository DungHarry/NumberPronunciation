/*
    Author: Dung Harry
    Date created: September 18th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the NormalDeleter class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_NORMAL_DELETER_H_
#define _COC_COC_NUMBER_PRONUNCIATION_NORMAL_DELETER_H_

#include "deleter.h"

template <class T>
class NormalDeleter : public Deleter<T> {
public:
    NormalDeleter() :
    Deleter<T>(DELETER_TYPE_NORMAL)
    {

    }

    virtual ~NormalDeleter() {

    }

    virtual void operator()(T *pPointer) {
        if(pPointer == nullptr)
            return;

        delete pPointer;
    }
};

#endif

