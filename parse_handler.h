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

    Description: this is the header file of the ParseHandler class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_PARSE_HANDLER_H_
#define _COC_COC_NUMBER_PRONUNCIATION_PARSE_HANDLER_H_

#include <memory>
#include <string>
#include <cinttypes>
#include "stream_utility.h"
#include "string_utility.h"
#include "config.h"
#include "handler.h"
#include "normal_digit_attribute.h"
#include "special_digit_attribute.h"
#include "multiple_digits_attribute.h"
#include "condition_append_attribute.h"
#include "condition_digit_attribute.h"
#include "condition_append_digits_end_attribute.h"

using namespace std;

class ParseHandler : public Handler {
public:
    ParseHandler();
    ParseHandler(const wchar_t *cpcBuffer);
    virtual ~ParseHandler();

    const wchar_t* getBuffer();
    void setBuffer(const wchar_t *cpcBuffer);

    virtual bool execute();

    Config* releaseConfig();

    static ParseHandler* getInstance();
protected:
    unique_ptr<Config> m_upConfig;
    unique_ptr<wstring> m_upsBuffer;
private:
    bool parseLanguage(const wchar_t *pwcLine, Config *pConfig);
    bool parseLocaleName(const wchar_t *pwcLine, Config *pConfig);
    bool parseNormalDigitAttribute(const wchar_t *pwcLine, Config *pConfig);
    bool parseSpecialDigitAttribute(const wchar_t *pwcLine, Config *pConfig);
    bool parseMultipleDigitsAttribute(const wchar_t *pwcLine, Config *pConfig);
    bool parseConditionAppendAttribute(const wchar_t *pwcLine, Config *pConfig);
    bool parseConditionDigitAttribute(const wchar_t *pwcLine, Config *pConfig);
    bool parseConditionAppendDigitsEndAttribute(const wchar_t *pwcLine, Config *pConfig);

    static unique_ptr<ParseHandler> m_upInstance;
};

#endif
