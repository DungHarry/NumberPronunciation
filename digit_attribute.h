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
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the DigitAttribute class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_DIGIT_ATTRIBUTE_H_
#define _COC_COC_NUMBER_PRONUNCIATION_DIGIT_ATTRIBUTE_H_

#include "attribute.h"
#include <utility>
#include <memory>
#include <string>

#define DIGIT_ATTRIBUTE_DIGIT_INVALID_VALUE (static_cast<char>('\0'))

class DigitAttribute : public Attribute {
public:
	DigitAttribute();
    DigitAttribute(AttributeType eType, int16_t iId, char cDigit, const wchar_t *cpcPronunciation);
	virtual ~DigitAttribute();

	virtual char getDigit();
	virtual void setDigit(const char cDigit);

    virtual const wchar_t* getPronunciation();
    virtual void setPronunciation(const wchar_t *cpcPronunciation);

	virtual bool less(const Comparable &attr);
	virtual bool equal(const Comparable &attr);
protected:
    unique_ptr<pair<char, unique_ptr<wstring>>> m_upCouple;
};

#endif
