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

    Description: this is the source code file of the ParseHandler class in C++ programming language
*/

#include "parse_handler.h"
#include "locale_handler.h"

#define PARSE_HANDLER_MULTIPLE_DIGITS_BUFFER_SIZE (static_cast<int32_t>(1 << 8))
#define PARSE_HANDLER_CONDITION_APPEND_END_DIGITS_BUFFER_SIZE (static_cast<int32_t>(1 << 8))
#define PARSE_HANDLER_DEFAULT_BUFFER_SIZE (static_cast<int32_t>(1 << 12))

unique_ptr<ParseHandler> ParseHandler::m_upInstance (nullptr);

ParseHandler::ParseHandler() :
    Handler(HANDLER_TYPE_PARSE),
    m_upConfig (nullptr),
    m_upsBuffer (new wstring())
{

}

ParseHandler::ParseHandler(const wchar_t *cpcBuffer) :
    Handler(HANDLER_TYPE_PARSE),
    m_upConfig (nullptr),
    m_upsBuffer (cpcBuffer == nullptr ? nullptr : new wstring(cpcBuffer))
{

}

ParseHandler::~ParseHandler() {
    if(this->m_upsBuffer.get() != nullptr)
        this->m_upsBuffer.reset();

    if(this->m_upConfig.get() != nullptr)
        this->m_upConfig.reset();
}

const wchar_t* ParseHandler::getBuffer() {
    return (this->m_upsBuffer.get() == nullptr) ? nullptr : this->m_upsBuffer->c_str();
}

void ParseHandler::setBuffer(const wchar_t *cpcBuffer) {
    if(cpcBuffer == nullptr)
        return;

    this->m_upsBuffer.reset(new wstring(cpcBuffer));
}

bool ParseHandler::execute() {
    wchar_t *pwcLine, *pwcCleanLine, wcFirstCharacter, wcSecondCharacter;

    if(this->m_upsBuffer.get() == nullptr)
        return false;

    StreamUtility::getInstance()->setContent(this->m_upsBuffer->c_str());

    this->m_upConfig.reset(new Config());

    for(pwcLine = nullptr; StreamUtility::getInstance()->isEndOfStream() == false; ) {
        if((pwcLine = StreamUtility::getInstance()->readLine()) == nullptr || wcslen(pwcLine) <= 0) {
            if(pwcLine != nullptr)
                delete[] pwcLine;

            continue;
        }

		pwcCleanLine = nullptr;

		if(StringUtility::getInstance()->clearWString(pwcLine, &pwcCleanLine) == false || pwcCleanLine == nullptr) {
            delete[] pwcLine;

            if(pwcCleanLine != nullptr)
                delete[] pwcCleanLine;

            continue;
		}

        if((wcFirstCharacter = *(pwcCleanLine + 0)) == static_cast<wchar_t>('l')) {
            if ((wcSecondCharacter = *(pwcCleanLine + 1)) == static_cast<wchar_t>('a'))
                this->parseLanguage(pwcCleanLine, this->m_upConfig.get());
            else if (wcSecondCharacter == static_cast<wchar_t>('o'))
                this->parseLocaleName(pwcCleanLine, this->m_upConfig.get());
        } else if(wcFirstCharacter == static_cast<wchar_t>('0'))
            this->parseNormalDigitAttribute(pwcCleanLine, this->m_upConfig.get());
        else if(wcFirstCharacter == static_cast<wchar_t>('1'))
            this->parseSpecialDigitAttribute(pwcCleanLine, this->m_upConfig.get());
        else if(wcFirstCharacter == static_cast<wchar_t>('2'))
            this->parseMultipleDigitsAttribute(pwcCleanLine, this->m_upConfig.get());
        else if(wcFirstCharacter == static_cast<wchar_t>('3'))
            this->parseConditionAppendAttribute(pwcCleanLine, this->m_upConfig.get());
        else if(wcFirstCharacter == static_cast<wchar_t>('4'))
            this->parseConditionAppendDigitsEndAttribute(pwcCleanLine, this->m_upConfig.get());
        else if(wcFirstCharacter == static_cast<wchar_t>('5'))
            this->parseConditionDigitAttribute(pwcCleanLine, this->m_upConfig.get());

        delete[] pwcCleanLine;

        delete[] pwcLine;
    }

    StreamUtility::getInstance()->clearContent();

	return this->m_upConfig->classify();
}

Config* ParseHandler::releaseConfig() {
    return this->m_upConfig.release();
}

ParseHandler* ParseHandler::getInstance() {
    if(m_upInstance.get() == nullptr)
        m_upInstance.reset(new ParseHandler());

    return m_upInstance.get();
}

bool ParseHandler::parseLanguage(const wchar_t *pwcLine, Config *pConfig) {
	wchar_t *pwcBuffer;
	char *pcLanguage;

    if(pwcLine == nullptr || pConfig == nullptr || pConfig->getLang() == nullptr)
        return false;

	pwcBuffer = new wchar_t[1 << 10];

    if (swscanf(pwcLine, L"lang %ls", pwcBuffer) != 1 || (pcLanguage = StringUtility::getInstance()->convertToChar(pwcBuffer)) == nullptr) {
		delete[] pwcBuffer;
		
		return false;
	}

    StringUtility::getInstance()->replaceCharacter(pwcBuffer, L'_', L' ');
    StringUtility::getInstance()->checkSpecialCaseAndReplace(&pwcBuffer, L"null", L"");

	pConfig->getLang()->setName(pcLanguage); 

	delete[] pwcBuffer;
	delete[] pcLanguage;

    return true;
}

bool ParseHandler::parseLocaleName(const wchar_t *pwcLine, Config *pConfig) {
	wchar_t *pwcBuffer;
	char *pcLocale;

	if (pwcLine == nullptr || pConfig == nullptr || pConfig->getLang() == nullptr)
		return false;

	pwcBuffer = new wchar_t[PARSE_HANDLER_DEFAULT_BUFFER_SIZE];

    if (swscanf(pwcLine, L"locale %ls", pwcBuffer) != 1 || (pcLocale = StringUtility::getInstance()->convertToChar(pwcBuffer)) == nullptr) {
		delete[] pwcBuffer;

		return false;
	}

    StringUtility::getInstance()->replaceCharacter(pwcBuffer, L'_', L' ');
    StringUtility::getInstance()->checkSpecialCaseAndReplace(&pwcBuffer, L"null", L"");

	pConfig->getLang()->setLocaleName(pcLocale);

	delete[] pwcBuffer;
	delete[] pcLocale;

	return true;
}

bool ParseHandler::parseNormalDigitAttribute(const wchar_t *pwcLine, Config *pConfig) {
	int16_t iId;
	wchar_t wcDigit;
	wchar_t *pwcBuffer;
    shared_ptr<Comparable> spNormalDigitAttribute (nullptr);

    if(pwcLine == nullptr || pConfig == nullptr || pConfig->getAttributes() == nullptr)
        return false;

	pwcBuffer = new wchar_t[PARSE_HANDLER_DEFAULT_BUFFER_SIZE];

    if (swscanf(pwcLine, L"0 %hd %lc %ls", &iId, &wcDigit, pwcBuffer) != 3) {
		delete[] pwcBuffer;

		return false;
	}

    StringUtility::getInstance()->replaceCharacter(pwcBuffer, L'_', L' ');
    StringUtility::getInstance()->checkSpecialCaseAndReplace(&pwcBuffer, L"null", L"");

    spNormalDigitAttribute.reset(new NormalDigitAttribute(iId, static_cast<char>(wcDigit), pwcBuffer));

    pConfig->getAttributes()->push_back(Container(spNormalDigitAttribute));

	delete[] pwcBuffer;

    return true;
}

bool ParseHandler::parseSpecialDigitAttribute(const wchar_t *pwcLine, Config *pConfig) {
	int16_t iId;
	wchar_t wcDigit;
	wchar_t *pwcBuffer;
    shared_ptr<Comparable> spSpecialDigitAttribute (nullptr);

    if(pwcLine == nullptr || pConfig == nullptr || pConfig->getAttributes() == nullptr)
        return false;

	pwcBuffer = new wchar_t[PARSE_HANDLER_DEFAULT_BUFFER_SIZE];

    if (swscanf(pwcLine, L"1 %hd %lc %ls", &iId, &wcDigit, pwcBuffer) != 3) {
		delete[] pwcBuffer;

		return false;
	}

    StringUtility::getInstance()->replaceCharacter(pwcBuffer, L'_', L' ');
    StringUtility::getInstance()->checkSpecialCaseAndReplace(&pwcBuffer, L"null", L"");

    spSpecialDigitAttribute.reset(new SpecialDigitAttribute(iId, static_cast<char>(wcDigit), pwcBuffer));

    pConfig->getAttributes()->push_back(Container(spSpecialDigitAttribute));

	delete[] pwcBuffer;

    return true;
}

bool ParseHandler::parseMultipleDigitsAttribute(const wchar_t *pwcLine, Config *pConfig) {
    int16_t iId;
	wchar_t *pwcDigitsBuffer, *pwcBuffer;
    shared_ptr<Comparable> spMultipleDigitsAttribute (nullptr);

    if(pwcLine == nullptr || pConfig == nullptr || pConfig->getAttributes() == nullptr)
        return false;

	pwcDigitsBuffer = new wchar_t[PARSE_HANDLER_MULTIPLE_DIGITS_BUFFER_SIZE];
	pwcBuffer = new wchar_t[PARSE_HANDLER_DEFAULT_BUFFER_SIZE];

    if (swscanf(pwcLine, L"2 %hd %ls %ls", &iId, pwcDigitsBuffer, pwcBuffer) != 3) {
		delete[] pwcDigitsBuffer;
		delete[] pwcBuffer;

		return false;
	}

    StringUtility::getInstance()->replaceCharacter(pwcBuffer, L'_', L' ');
    StringUtility::getInstance()->replaceCharacter(pwcDigitsBuffer, L'_', L' ');

    StringUtility::getInstance()->checkSpecialCaseAndReplace(&pwcBuffer, L"null", L"");
    StringUtility::getInstance()->checkSpecialCaseAndReplace(&pwcDigitsBuffer, L"null", L"");

    spMultipleDigitsAttribute.reset(new MultipleDigitsAttribute(iId, pwcDigitsBuffer, pwcBuffer));

    pConfig->getAttributes()->push_back(Container(spMultipleDigitsAttribute));

	delete[] pwcDigitsBuffer;
	delete[] pwcBuffer;

    return true;
}

bool ParseHandler::parseConditionAppendAttribute(const wchar_t *pwcLine, Config *pConfig) {
    int16_t iId, iPosition;
	wchar_t *pwcBuffer;
    shared_ptr<Comparable> spConditionAppendAttribute (nullptr);

    if(pwcLine == nullptr || pConfig == nullptr || pConfig->getAttributes() == nullptr)
        return false;

	pwcBuffer = new wchar_t[PARSE_HANDLER_DEFAULT_BUFFER_SIZE];

    if (swscanf(pwcLine, L"3 %hd %hd %ls", &iId, &iPosition, pwcBuffer) != 3) {
		delete[] pwcBuffer;

		return false;
	}

    StringUtility::getInstance()->replaceCharacter(pwcBuffer, L'_', L' ');
    StringUtility::getInstance()->checkSpecialCaseAndReplace(&pwcBuffer, L"null", L"");

    spConditionAppendAttribute.reset(new ConditionAppendAttribute(iId, iPosition, pwcBuffer));

    pConfig->getAttributes()->push_back(Container(spConditionAppendAttribute));

	delete[] pwcBuffer;

    return true;
}

bool ParseHandler::parseConditionAppendDigitsEndAttribute(const wchar_t *pwcLine, Config *pConfig) {
    int16_t iId, iPosition;
    wchar_t *pwcEndDigitsBuffer, *pwcBuffer;
    shared_ptr<Comparable> spConditionAppendDigitsEndAttribute (nullptr);

    if(pwcLine == nullptr || pConfig == nullptr || pConfig->getAttributes() == nullptr)
        return false;

    pwcEndDigitsBuffer = new wchar_t[PARSE_HANDLER_CONDITION_APPEND_END_DIGITS_BUFFER_SIZE];
    pwcBuffer = new wchar_t[PARSE_HANDLER_DEFAULT_BUFFER_SIZE];

    if(swscanf(pwcLine, L"4 %hd %hd %ls %ls", &iId, &iPosition, pwcEndDigitsBuffer, pwcBuffer) != 4) {
        delete[] pwcEndDigitsBuffer;
        delete[] pwcBuffer;

        return false;
    }

    StringUtility::getInstance()->replaceCharacter(pwcEndDigitsBuffer, L'_', L' ');
    StringUtility::getInstance()->checkSpecialCaseAndReplace(&pwcEndDigitsBuffer, L"null", L"");

    StringUtility::getInstance()->replaceCharacter(pwcBuffer, L'_', L' ');
    StringUtility::getInstance()->checkSpecialCaseAndReplace(&pwcBuffer, L"null", L"");

    spConditionAppendDigitsEndAttribute.reset(new ConditionAppendDigitsEndAttribute(iId, iPosition, pwcEndDigitsBuffer, pwcBuffer));

    pConfig->getAttributes()->push_back(Container(spConditionAppendDigitsEndAttribute));

    delete[] pwcEndDigitsBuffer;
    delete[] pwcBuffer;

    return true;
}

bool ParseHandler::parseConditionDigitAttribute(const wchar_t *pwcLine, Config *pConfig) {
    int16_t iId, iPosition;
	wchar_t wcDigit;
	wchar_t *pwcBuffer;
    shared_ptr<Comparable> spConditionDigitAttribute (nullptr);

    if(pwcLine == nullptr || pConfig == nullptr || pConfig->getAttributes() == nullptr)
        return false;

	pwcBuffer = new wchar_t[PARSE_HANDLER_DEFAULT_BUFFER_SIZE];

    if (swscanf(pwcLine, L"5 %hd %lc %hd %ls", &iId, &wcDigit, &iPosition, pwcBuffer) != 4) {
		delete[] pwcBuffer;

		return false;
	}

    StringUtility::getInstance()->replaceCharacter(pwcBuffer, L'_', L' ');
    StringUtility::getInstance()->checkSpecialCaseAndReplace(&pwcBuffer, L"null", L"");

    spConditionDigitAttribute.reset(new ConditionDigitAttribute(iPosition, iId, static_cast<char>(wcDigit), pwcBuffer));

    pConfig->getAttributes()->push_back(Container(spConditionDigitAttribute));

	delete[] pwcBuffer;

    return true;
}
