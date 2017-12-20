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
    Date created: August 21th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the MultipleDigitsAttribute class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_MULTIPLE_DIGITS_ATTRIBUTE_H_
#define _COC_COC_NUMBER_PRONUNCIATION_MULTIPLE_DIGITS_ATTRIBUTE_H_

#include <utility>
#include <memory>
#include <string>
#include "attribute.h"

class MultipleDigitsAttribute : public Attribute {
public:
    MultipleDigitsAttribute();
    MultipleDigitsAttribute(int16_t iId, const wchar_t *cpcDigits, const wchar_t *cpcPronunciation);
    MultipleDigitsAttribute(const MultipleDigitsAttribute &attr);
    virtual ~MultipleDigitsAttribute();

    virtual const wchar_t* getDigits();
    virtual void setDigits(const wchar_t *cpcDigits);

    virtual const wchar_t* getPronunciation();
    virtual void setPronunciation(const wchar_t *cpcPronunciation);

	virtual bool less(const Comparable &attr);
	virtual bool equal(const Comparable &attr);
private:
    unique_ptr<pair<unique_ptr<wstring>, unique_ptr<wstring>>> m_upCouple;
};

#endif
