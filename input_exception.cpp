/*
    Author: Dung Ly Viet
    Date created: September 13th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the InputException class in C++ programming language
*/

#include "input_exception.h"

InputException::InputException() :
    Exception(EXCEPTION_TYPE_INPUT, "Input exception common"),
    m_eReason (INPUT_EXCEPTION_REASON_NONE)
{
    this->autoGenerateMessage();
}

InputException::InputException(InputExceptionReason eReason) :
    Exception(EXCEPTION_TYPE_INPUT, "Input exception common"),
    m_eReason (eReason)
{
    this->autoGenerateMessage();
}

InputException::InputException(const InputException &e) :
    Exception(e),
    m_eReason (e.m_eReason)
{
    this->autoGenerateMessage();
}

InputException::~InputException() {

}

InputExceptionReason InputException::getReason() {
    return this->m_eReason;
}

void InputException::setReason(const InputExceptionReason eReason) {
    if(this->m_eReason < INPUT_EXCEPTION_REASON_NONE || this->m_eReason >= INPUT_EXCEPTION_REASON_COUNT)
        return;

    this->m_eReason = eReason;

    this->autoGenerateMessage();
}

bool InputException::autoGenerateMessage() {
    if(this->m_eReason < INPUT_EXCEPTION_REASON_NONE || this->m_eReason >= INPUT_EXCEPTION_REASON_COUNT)
        return false;

    if(this->m_eReason == INPUT_EXCEPTION_REASON_NONE)
        this->m_upsMessage.reset(new string("Input exception common"));
    else if(this->m_eReason == INPUT_EXCEPTION_REASON_EXCEED_TRY_COUNT)
        this->m_upsMessage.reset(new string("Exceeded number of tries count"));
    else
        this->m_upsMessage.reset(new string("Unknown input exception"));

    return true;
}
