/*
    NumberPronunciation provides a way to pronounce a number
    Copyright (C) 2017 of Dung Harry

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.

    Author: Dung Harry
    Date created: September 3rd, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the ConfigName class in C++ programming language
*/

#include "config_name.h"

template <class T>
ConfigName<T>::ConfigName() :
    Object(OBJECT_TYPE_CONFIG_FILE),
    m_iId (CONFIG_NAME_ID_INVALID_ID),
    m_upsValue (new basic_string<T>())
{

}

template <class T>
ConfigName<T>::ConfigName(int16_t iId, const T *cpcValue) :
    Object(OBJECT_TYPE_CONFIG_FILE),
    m_iId (iId),
    m_upsValue (cpcValue == nullptr ? new basic_string<T>() : new basic_string<T>(cpcValue))
{

}

template <class T>
ConfigName<T>::ConfigName(const ConfigName &cf) :
    Object (OBJECT_TYPE_CONFIG_FILE),
    m_iId (cf.m_iId),
    m_upsValue (cf.m_upsValue.get() == nullptr ? new basic_string<T>() : new basic_string<T>(cf.m_upsValue->c_str()))
{

}

template <class T>
ConfigName<T>::~ConfigName() {
    if(this->m_upsValue.get() != nullptr)
        this->m_upsValue.reset();
}

template <class T>
const T* ConfigName<T>::getValue() {
    return this->m_upsValue.get() == nullptr ? nullptr : this->m_upsValue->c_str();
}

template <class T>
void ConfigName<T>::setValue(const T *cpcValue) {
    if(cpcValue == nullptr)
        this->m_upsValue.reset();
    else
        this->m_upsValue.reset(new basic_string<T>(cpcValue));
}

template <class T>
int16_t ConfigName<T>::getId() {
    return this->m_iId;
}

template <class T>
void ConfigName<T>::setId(const int16_t iId) {
    this->m_iId = iId;
}

template <class T>
bool ConfigName<T>::less(const Comparable &com) {
    const ConfigName<T> *pConfig = dynamic_cast<const ConfigName<T>*>(&com);

    return (pConfig == nullptr) ? false : (this->m_iId < pConfig->m_iId);
}

template <class T>
bool ConfigName<T>::equal(const Comparable &com) {
    const ConfigName<T> *pConfig = dynamic_cast<const ConfigName<T>*>(&com);

    return (pConfig == nullptr) ? false : (this->m_iId == pConfig->m_iId);
}
