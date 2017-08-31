/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Handler class in C++ programming language
*/

#include "handler.h"

Handler::Handler() :
    m_eType (HANDLER_TYPE_NONE)
{

}

Handler::Handler(HandlerType eType) :
    m_eType (eType < 0 || eType >= HANDLER_TYPE_COUNT ? HANDLER_TYPE_NONE : eType)
{

}

Handler::~Handler() {

}

bool Handler::execute() {
	return true;
}

HandlerType Handler::getType() {
    return this->m_eType;
}

void Handler::setType(HandlerType eType) {
    if(eType < 0 || eType >= HANDLER_TYPE_COUNT)
        return;

    this->m_eType = eType;
}
