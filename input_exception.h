/*
    Author: Dung Ly Viet
    Date created: September 13th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the InputException class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_INPUT_EXCEPTION_H_
#define _COC_COC_NUMBER_PRONUNCIATION_INPUT_EXCEPTION_H_

#include "exception.h"

enum InputExceptionReason {
    INPUT_EXCEPTION_REASON_NONE = 0,
    INPUT_EXCEPTION_REASON_EXCEED_TRY_COUNT,
    INPUT_EXCEPTION_REASON_COUNT
};

class InputException : public Exception {
public:
    InputException();
    InputException(InputExceptionReason eReason);
    InputException(const InputException &e);
    virtual ~InputException();

    InputExceptionReason getReason();
    void setReason(const InputExceptionReason eReason);
protected:
    InputExceptionReason m_eReason;

  private:
    bool autoGenerateMessage();
};

#endif

