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
	Date created: August 25th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Number class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_NUMBER_H_
#define _COC_COC_NUMBER_PRONUNCIATION_NUMBER_H_

#include <memory>
#include <vector>
#include "object.h"
#include "normal_digit.h"

#define NUMBER_LOWEST_UNIT_INVALID_VALUE (static_cast<int32_t>(-1))

class Number : public Object {
public:
	Number();
	Number(const int32_t iLowestUnit);
	virtual ~Number();

	virtual int32_t getLowestUnit();
	virtual void setLowestUnit(const int32_t iLowestUnit);

	virtual vector<unique_ptr<Object>>* getNumbers();

	bool verifyIgnoreToDigits();
protected:
	int32_t m_iLowestUnit;
	unique_ptr<vector<unique_ptr<Object>>> m_upNumbers;

private:
    bool verifyIgnoreToFloatingPointPart(Number *pNumber);
    bool verifyIgnoreToFloatingPointPart(Object *pObject, bool &bNonZero);
    bool verifyIgnoreToNumberUnit(Number *pNumber, bool &bNonZeroGlobal, int32_t iLevel, int32_t &iNumberUnitOffset);
	bool verifyIgnoreToObject(Object *pObject, bool &bNonZeroGlobal, bool &bNonZeroLocal, int32_t &iNumberUnitOffset);
	
	bool verifyIgnoreToNumberUnitAgain(Number *pNumber);

    bool isAllThreeZeroDigits(Number *pNumber);
};

#endif
