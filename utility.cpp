/*
    Author: Dung Ly Viet
    Date created: August 22th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the Utility class in C++ programming language
*/

#include "utility.h"

Utility::Utility() :
    m_eType (UTILITY_TYPE_NONE)
{

}

Utility::Utility(UtilityType eType) :
    m_eType (eType < 0 || eType >= UTILITY_TYPE_COUNT ? UTILITY_TYPE_NONE : eType)
{

}

Utility::~Utility() {

}

UtilityType Utility::getType() {
    return this->m_eType;
}

void Utility::setType(UtilityType eType) {
    if(eType < 0 || eType >= UTILITY_TYPE_COUNT)
        return;

    this->m_eType = eType;
}
