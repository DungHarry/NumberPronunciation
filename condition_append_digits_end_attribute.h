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
    Date created: September 22th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the ConditionAppendDigitsEndAttribute class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_CONDITION_APPEND_DIGITS_END_ATTRIBUTE_H_
#define _COC_COC_NUMBER_PRONUNCIATION_CONDITION_APPEND_DIGITS_END_ATTRIBUTE_H_

#include <utility>
#include <memory>
#include <string>
#include "attribute.h"

#define CONDITION_APPEND_DIGITS_END_ATTRIBUTE_INVALID_UNITS (static_cast<int16_t>(-1))

class ConditionAppendDigitsEndAttribute : public Attribute {
public:
    ConditionAppendDigitsEndAttribute();
    ConditionAppendDigitsEndAttribute(int16_t iId, int16_t iPosition, const wchar_t *cpwcDigitsEnd, const wchar_t *cpwcPronunciation);
    virtual ~ConditionAppendDigitsEndAttribute();

    virtual int16_t getUnits();
    virtual void setUnits(const int16_t iUnits);

    virtual const wchar_t* getDigitsEnd();
    virtual void setDigitsEnd(const wchar_t *cpwcDigitsEnd);

    virtual const wchar_t* getPronunciation();
    virtual void setPronunciation(const wchar_t *cpwcPronunciation);

    virtual bool less(const Comparable &attr);
    virtual bool equal(const Comparable &attr);
private:
    int16_t m_iUnits;
    unique_ptr<wstring> m_upDigitsEnd;
    unique_ptr<wstring> m_upPronunciation;
};

#endif

