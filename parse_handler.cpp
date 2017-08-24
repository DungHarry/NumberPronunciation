/*
    Author: Dung Ly Viet
    Date created: August 17th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the ParseHandler class in C++ programming language
*/

#include "parse_handler.h"

auto_ptr<ParseHandler> ParseHandler::m_apInstance (NULL);

ParseHandler::ParseHandler() :
    Handler(HANDLER_TYPE_PARSE),
    m_apConfig (NULL),
    m_apsBuffer (new wstring())
{

}

ParseHandler::ParseHandler(const wchar_t *cpcBuffer) :
    Handler(HANDLER_TYPE_PARSE),
    m_apConfig (NULL),
    m_apsBuffer (cpcBuffer == NULL ? NULL : new wstring(cpcBuffer))
{

}

ParseHandler::~ParseHandler() {
    if(this->m_apsBuffer.get() != NULL)
        this->m_apsBuffer.reset();

    if(this->m_apConfig.get() != NULL)
        this->m_apConfig.reset();
}

const wchar_t* ParseHandler::getBuffer() {
    return (this->m_apsBuffer.get() == NULL) ? NULL : this->m_apsBuffer->c_str();
}

void ParseHandler::setBuffer(const wchar_t *cpcBuffer) {
    if(cpcBuffer == NULL)
        return;

    this->m_apsBuffer.reset(new wstring(cpcBuffer));
}

bool ParseHandler::execute() {
    wchar_t *pwcLine, *pwcCleanLine, wcFirstCharacter, wcSecondCharacter;

    if(this->m_apsBuffer.get() == NULL)
        return false;

    StreamUtility::getInstance()->setContent(this->m_apsBuffer->c_str());

    this->m_apConfig.reset(new Config());

    while(StreamUtility::getInstance()->isEndOfStream() == false) {
        if((pwcLine = StreamUtility::getInstance()->readLine()) == NULL || wcslen(pwcLine) <= 0) {
            delete[] pwcLine;

            continue;
        }

		pwcCleanLine = NULL;

		if(StringUtility::getInstance()->clearWString(pwcLine, &pwcCleanLine) == false || pwcCleanLine == NULL) {
			this->m_apConfig.reset(new Config());

			if((wcFirstCharacter = *(pwcCleanLine + 0)) == static_cast<wchar_t>('l')) {
				if ((wcSecondCharacter = *(pwcCleanLine + 1)) == static_cast<wchar_t>('a'))
					this->parseLanguage(pwcCleanLine, this->m_apConfig.get());
				else if (wcSecondCharacter == static_cast<wchar_t>('o'))
					this->parseLocaleName(pwcCleanLine, this->m_apConfig.get());
			} else if(wcFirstCharacter == static_cast<wchar_t>('0'))
				this->parseNormalDigitAttribute(pwcCleanLine, this->m_apConfig.get());
			else if(wcFirstCharacter == static_cast<wchar_t>('1'))
				this->parseSpecialDigitAttribute(pwcCleanLine, this->m_apConfig.get());
			else if(wcFirstCharacter == static_cast<wchar_t>('2'))
				this->parseMultipleDigitsAttribute(pwcCleanLine, this->m_apConfig.get());
			else if(wcFirstCharacter == static_cast<wchar_t>('3'))
				this->parseConditionAppendAttribute(pwcCleanLine, this->m_apConfig.get());
			else if(wcFirstCharacter == static_cast<wchar_t>('4'))
				this->parseConditionDigitAttribute(pwcCleanLine, this->m_apConfig.get());

			delete[] pwcCleanLine;
		}

        delete[] pwcLine;
    }

    StreamUtility::getInstance()->clearContent();

    return true;
}

Config* ParseHandler::releaseConfig() {
    Config *pConfig = this->m_apConfig.get();

    this->m_apConfig.release();

    return pConfig;
}

ParseHandler* ParseHandler::getInstance() {
    if(m_apInstance.get() == NULL)
        m_apInstance.reset(new ParseHandler());

    return m_apInstance.get();
}

bool ParseHandler::parseLanguage(const wchar_t *pwcLine, Config *pConfig) {
	wchar_t *pwcBuffer;
	char *pcLanguage;

    if(pwcLine == NULL || pConfig == NULL || pConfig->getLang() == NULL)
        return false;

	pwcBuffer = new wchar_t[1 << 10];

	if (swscanf(pwcLine, L"lang %ls", pwcBuffer) == EOF || (pcLanguage = StringUtility::getInstance()->convertToChar(pwcBuffer)) == NULL) {
		delete[] pwcBuffer;
		
		return false;
	}

	pConfig->getLang()->setName(pcLanguage); 

	delete[] pwcBuffer;
	delete[] pcLanguage;

    return true;
}

bool ParseHandler::parseLocaleName(const wchar_t *pwcLine, Config *pConfig) {
	wchar_t *pwcBuffer;
	char *pcLocale;

	if (pwcLine == NULL || pConfig == NULL || pConfig->getLang() == NULL)
		return false;

	pwcBuffer = new wchar_t[1 << 10];

	if (swscanf(pwcLine, L"locale %ls", pwcBuffer) || (pcLocale = StringUtility::getInstance()->convertToChar(pwcBuffer)) == NULL) {
		delete[] pwcBuffer;

		return false;
	}

	pConfig->getLang()->setName(pcLocale);

	delete[] pwcBuffer;
	delete[] pcLocale;

	return true;
}

bool ParseHandler::parseNormalDigitAttribute(const wchar_t *pwcLine, Config *pConfig) {
    if(pwcLine == NULL || pConfig == NULL)
        return false;

    return true;
}

bool ParseHandler::parseSpecialDigitAttribute(const wchar_t *pwcLine, Config *pConfig) {
    if(pwcLine == NULL || pConfig == NULL)
        return false;

    return true;
}

bool ParseHandler::parseMultipleDigitsAttribute(const wchar_t *pwcLine, Config *pConfig) {
    if(pwcLine == NULL || pConfig == NULL)
        return false;

    return true;
}

bool ParseHandler::parseConditionAppendAttribute(const wchar_t *pwcLine, Config *pConfig) {
    if(pwcLine == NULL || pConfig == NULL)
        return false;

    return true;
}

bool ParseHandler::parseConditionDigitAttribute(const wchar_t *pwcLine, Config *pConfig) {
    if(pwcLine == NULL || pConfig == NULL)
        return false;

    return true;
}
