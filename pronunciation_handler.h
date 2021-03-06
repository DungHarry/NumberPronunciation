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
	Date created: August 29th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the PronunciationHandler class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_PRONUNCIATION_HANDLER_H_
#define _COC_COC_NUMBER_PRONUNCIATION_PRONUNCIATION_HANDLER_H_

#include <string>
#include <memory>
#include "handler.h"
#include "number.h"
#include "config.h"
#include "special_digit.h"
#include "normal_digit.h"
#include "normal_digit_attribute.h"
#include "special_digit_attribute.h"
#include "multiple_digits_attribute.h"
#include "condition_append_attribute.h"
#include "condition_digit_attribute.h"
#include "condition_append_digits_end_attribute.h"
#include "string_utility.h"
#include "search_utility.h"

enum PronunciationHandlerState {
	PRONUNCIATION_HANDLER_STATE_NONE = 0,
	PRONUNCIATION_HANDLER_STATE_SPECIAL_DIGIT,
	PRONUNCIATION_HANDLER_STATE_NUMBER_UNIT,
	PRONUNCIATION_HANDLER_STATE_MULTIPLE_DIGITS,
    PRONUNCIATION_HANDLER_STATE_MULTIPLE_DIGITS_WITH_ZERO_APPENDED,
	PRONUNCIATION_HANDLER_STATE_NORMAL_DIGIT,
	PRONUNCIATION_HANDLER_STATE_CONDITION_DIGIT,
	PRONUNCIATION_HANDLER_STATE_CONDITION_APPEND,
    PRONUNCIATION_HANDLER_STATE_CONDITION_APPEND_END_DIGTS,
	PRONUNCIATION_HANDLER_STATE_COUNT
};

class PronunciationHandler : public Handler {
public:
	PronunciationHandler();
	PronunciationHandler(Config *pConfig, Number *pNumber);
	virtual ~PronunciationHandler();

	virtual bool execute();

	Config* getConfig();
	void setConfig(Config *pConfig);

	Number* getNumber();
	void setNumber(Number *pNumber);

	wstring* getPronunciation(); 
	wstring* releasePronunciation();

	static PronunciationHandler* getInstance();
protected:
	unique_ptr<Config> m_upConfig;
	unique_ptr<Number> m_upNumber;
	unique_ptr<wstring> m_upwsPronunciation;
private:
	PronunciationHandlerState detectExecutionState(Object *pObject);
	bool processState(const PronunciationHandlerState eState, Object *pObject, int32_t iLength, int32_t iUnit);

	bool processNumberUnit(Number *pNumber);

	bool handleNumberUnitNumDigits(Number *pNumber, int32_t iNumDigits);

	bool pronounceSpecialDigit(const char cDigit);
	bool pronounceMutipleDigits(const char *cpcMultipleDigits);
    bool pronounceMutipleDigitsWithZeroAppended(char cDigit, int32_t iUnit);
	bool pronounceConditionDigit(const char cDigit, const int16_t iDigitPosition);
	bool pronounceNormalDigit(const char cDigit);
	bool pronounceConditionAppend(const int16_t iDigitPosition);
    bool pronounceConditionAppendEndDigits(const int16_t iDigitPosition, const char *cpcEndDigits);

    bool isAllThreeZeroDigits(Number *pNumber);

	static unique_ptr<PronunciationHandler> m_upInstance;
};

#endif
