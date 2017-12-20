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
    Date created: August 22th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the StringUtility class in C++ programming language
*/

#include "string_utility.h"

unique_ptr<StringUtility> StringUtility::m_upInstance ( nullptr );

StringUtility::StringUtility() :
    Utility(UTILITY_TYPE_STRING)
{

}

StringUtility::~StringUtility() {

}

wchar_t* StringUtility::convertToWChar(const char *cpcString) {
    wchar_t *pcResult;
    int32_t iSize, iReturn;

    if(cpcString == nullptr)
        return nullptr;

    pcResult = new wchar_t[(iSize = strlen(cpcString) + 1)];

    while((iReturn = mbstowcs(pcResult, cpcString, iSize)) >= iSize) {
        iSize = iReturn + 1;

        delete[] pcResult;

        pcResult = new wchar_t[iSize];
    }

    return pcResult;
}

char* StringUtility::convertToChar(const wchar_t *cpcString) {
    char *pcResult;
    int32_t iSize, iReturn;

    if(cpcString == nullptr)
        return nullptr;

    pcResult = new char[(iSize = wcslen(cpcString) + 1)];

    while((iReturn = wcstombs(pcResult, cpcString, iSize)) >= iSize) {
        iSize = iReturn + 1;

        delete[] pcResult;

        pcResult = new char[iSize];
    }

    return pcResult;
}

wstring* StringUtility::convertToWString(const string *psString) {
    wstring *pwsResult;
    wchar_t *pwcBuffer;

    if(psString == nullptr || psString->size() <= 0 || (pwcBuffer = this->convertToWChar(psString->c_str())) == nullptr)
        return nullptr;

    pwsResult = new wstring(pwcBuffer);

    delete[] pwcBuffer;

    return pwsResult;
}

string* StringUtility::convertToString(const wstring *pwsString) {
    string *psResult;
    char *pcBuffer;

    if(pwsString == nullptr || pwsString->size() <= 0 || (pcBuffer = this->convertToChar(pwsString->c_str())) == nullptr)
        return nullptr;

    psResult = new string(pcBuffer);

    delete[] pcBuffer;

    return psResult;
}

bool StringUtility::clearString(const char *pcString, char **pcResult) {
    int32_t iStringLength;
    int32_t i, iStartIndex, iEndIndex;
    bool bCommentContain;

    if(pcString == nullptr || (iStringLength = strlen(pcString)) <= 0 || pcResult == nullptr || *pcResult != nullptr)
        return false;

    for(bCommentContain = false, i = 0; i < iStringLength - 1; i ++)
        if(*(pcString + i) == static_cast<char>(0x2F) && *(pcString + i + 1) == static_cast<char>(0x2F)) {
            bCommentContain = true;

            break;
        }

    for(iStartIndex = 0; iStartIndex < iStringLength && *(pcString + iStartIndex) == ' '; iStartIndex ++);

    for(iEndIndex = bCommentContain ? i - 1 : iStringLength - 1; iEndIndex >= 0 && *(pcString + iEndIndex) == ' '; iEndIndex --);

    if(iStartIndex >= iEndIndex)
        return false;

    *pcResult = new char[(iEndIndex - iStartIndex) + 2];

    for(i = iStartIndex; i <= iEndIndex; i ++)
        *((*pcResult) + i - iStartIndex) = *(pcString + i);

    *((*pcResult) + (iEndIndex - iStartIndex) + 1) = '\0';

    return true;
}

bool StringUtility::clearWString(const wchar_t *pwcString, wchar_t **pwcResult) {
    int32_t iStringLength;
    int32_t i, iStartIndex, iEndIndex;
    bool bCommentContain;

    if(pwcString == nullptr || (iStringLength = wcslen(pwcString)) <= 0 || pwcResult == nullptr || *pwcResult != nullptr)
        return false;

    for(bCommentContain = false, i = 0; i < iStringLength - 1; i ++)
        if(*(pwcString + i) == static_cast<wchar_t>(0x2F) && *(pwcString + i + 1) == static_cast<wchar_t>(0x2F)) {
            bCommentContain = true;

            break;
        }

    for(iStartIndex = 0; iStartIndex < iStringLength && *(pwcString + iStartIndex) == L' '; iStartIndex ++);

    for(iEndIndex = bCommentContain ? i - 1 : iStringLength - 1; iEndIndex >= 0 && *(pwcString + iEndIndex) == L' '; iEndIndex --);

    if(iStartIndex >= iEndIndex)
        return false;

    *pwcResult = new wchar_t[(iEndIndex - iStartIndex) + 2];

    for(i = iStartIndex; i <= iEndIndex; i ++)
        *((*pwcResult) + i - iStartIndex) = *(pwcString + i);

    *((*pwcResult) + (iEndIndex - iStartIndex) + 1) = L'\0';

    return true;
}

bool StringUtility::existWChar(const wchar_t *cpwcString, const wchar_t wcCharacter) {
    int32_t iLength, i;

    if(cpwcString == nullptr)
        return false;

    for(i = 0, iLength = wcslen(cpwcString); *(cpwcString + i) != wcCharacter && i < iLength; i ++);

    return (i < iLength);
}

bool StringUtility::existChar(const char *cpcString, const char cCharacter) {
    int32_t iLength, i;

    if(cpcString == nullptr)
        return false;

    for(i = 0, iLength = strlen(cpcString); *(cpcString + i) != cCharacter && i < iLength; i ++);

    return (i < iLength);
}

char* StringUtility::getSubStringNumber(Number *pNumber, int32_t iLength) {
	char *pcResult;
	NormalDigit *pNormalDigit;
	int32_t i;

	if (iLength <= 0 || pNumber == nullptr || pNumber->getNumbers() == nullptr || pNumber->getNumbers()->size() < iLength)
		return nullptr;

	pcResult = new char[iLength + 1];

	for (i = 0; i < iLength; i++)
        *(pcResult + i) = ((*(pNumber->getNumbers()->data() + iLength - 1 - i)).get() == nullptr || (pNormalDigit = dynamic_cast<NormalDigit *>((*(pNumber->getNumbers()->data() + iLength - 1 -i)).get())) == nullptr) ? '0' : pNormalDigit->getValue();

	*(pcResult + iLength) = '\0';

	return pcResult;
}

char* StringUtility::getSubStringNumber(Number *pNumber, int32_t iStartPosition, int32_t iLength) {
    char *pcResult;
    NormalDigit *pNormalDigit;
    int32_t i;

    if (iLength <= 0 || pNumber == nullptr || pNumber->getNumbers() == nullptr || iStartPosition < 0 || pNumber->getNumbers()->size() - iStartPosition < iLength)
        return nullptr;

    pcResult = new char[iLength + 1];

    for (i = 0; i < iLength; i++)
        *(pcResult + i) = ((*(pNumber->getNumbers()->data() + pNumber->getNumbers()->size() - 1 - i - iStartPosition)).get() == nullptr || (pNormalDigit = dynamic_cast<NormalDigit *>((*(pNumber->getNumbers()->data() + pNumber->getNumbers()->size() - 1 - i - iStartPosition)).get())) == nullptr) ? '0' : pNormalDigit->getValue();

    *(pcResult + iLength) = '\0';

    return pcResult;
}

char StringUtility::getCharacterNumber(Number *pNumber, int32_t iPosition) {
    Digit *pDigit;

    if(pNumber == nullptr || pNumber->getNumbers() == nullptr || pNumber->getNumbers()->size() <= 0 || iPosition < 0 || iPosition >= pNumber->getNumbers()->size())
        return '\0';

    if((pDigit = dynamic_cast<Digit *>(pNumber->getNumbers()->at(iPosition).get())) == nullptr)
        return '\0';

    return pDigit->getValue();
}

char* StringUtility::appendZero(const char cDigit, int32_t iCount) {
    char *pcResult;
    int32_t i;

    if(iCount <= 0)
        return nullptr;

    pcResult = new char[2 + iCount];

    *(pcResult + 0) = cDigit;

    for(i = 0; i < iCount; i ++)
        *(pcResult + 1 + i) = '0';

    *(pcResult + 1 + i) = '\0';

    return pcResult;
}

wchar_t* StringUtility::appendZero(const wchar_t wcDigit, int32_t iCount) {
    wchar_t *pwcResult;
    int32_t i;

    if(iCount <= 0)
        return nullptr;

    pwcResult = new wchar_t[2 + iCount];

    *(pwcResult + 0) = wcDigit;

    for(i = 0; i < iCount; i ++)
        *(pwcResult + 1 + i) = L'0';

    *(pwcResult + 1 + i) = L'\0';

    return pwcResult;
}

bool StringUtility::isAllDigitsValid(const char *cpcString, Config *pConfig) {
	set<Container> *pNormalDigitAttributeSet = nullptr, *pSpecialDigitAttributeSet = nullptr;
	int32_t i, iStringLength;
	Container c;
    shared_ptr<Comparable> spDigitAttribute (nullptr);

    if (cpcString == nullptr || pConfig == nullptr || (pNormalDigitAttributeSet = pConfig->getNormalDigitAttributes()) == nullptr || (pSpecialDigitAttributeSet = pConfig->getSpecialDigitAttributes()) == nullptr)
		return false;

	for (iStringLength = strlen(cpcString), i = 0; i < iStringLength; i++) {
        spDigitAttribute.reset(new NormalDigitAttribute(0, *(cpcString + i), nullptr));

        c.setData(spDigitAttribute);

        spDigitAttribute.reset();

        if (pNormalDigitAttributeSet != nullptr && pNormalDigitAttributeSet->find(c) != pNormalDigitAttributeSet->end())
			continue;

        spDigitAttribute.reset(new SpecialDigitAttribute(0, *(cpcString + i), nullptr));

        c.setData(spDigitAttribute);

        spDigitAttribute.reset();

        if (pSpecialDigitAttributeSet != nullptr && pSpecialDigitAttributeSet->find(c) != pSpecialDigitAttributeSet->end())
			continue;

        break;
	}

	return (i < iStringLength) ? false : true;
}

bool StringUtility::checkSpecialCaseAndReplace(char **pcString, const char *pcSpecialString, const char *pcReplaceString) {
    if(pcString == nullptr || *pcString == nullptr || pcSpecialString == nullptr || strcmp(*pcString, pcSpecialString) != 0)
        return false;

    if(pcReplaceString != nullptr) {
        free(*pcString);

        *pcString = (char *) malloc(sizeof(char) * (strlen(pcReplaceString) + 1));

        strcpy(*pcString, pcReplaceString);
    }

    return true;
}

bool StringUtility::checkSpecialCaseAndReplace(wchar_t **pwcString, const wchar_t *pwcSpecialString, const wchar_t *pwcReplaceString) {
    if(pwcString == nullptr || *pwcString == nullptr || pwcSpecialString == nullptr || wcscmp(*pwcString, pwcSpecialString) != 0)
        return false;

    if(pwcReplaceString != nullptr) {
        free(*pwcString);

        *pwcString = (wchar_t *) malloc(sizeof(wchar_t) * (wcslen(pwcReplaceString) + 1));

        wcscpy(*pwcString, pwcReplaceString);
    }

    return true;
}

bool StringUtility::replaceCharacter(char *pcString, char cSource, char cTarget) {
    int32_t i, iStringLength;

    if(pcString == nullptr || cSource == '\0' || cTarget == '\0')
        return false;

    for(i = 0, iStringLength = strlen(pcString); i < iStringLength; ++ i)
        if(*(pcString + i) == cSource)
            *(pcString + i) = cTarget;

    return true;
}

bool StringUtility::replaceCharacter(wchar_t *pwcString, wchar_t wcSource, wchar_t wcTarget) {
    int32_t i, iStringLength;

    if(pwcString == nullptr || wcSource == L'\0' || wcTarget == L'\0')
        return false;

    for(i = 0, iStringLength = wcslen(pwcString); i < iStringLength; ++ i)
        if(*(pwcString + i) == wcSource)
            *(pwcString + i) = wcTarget;

    return true;
}

bool StringUtility::eraseCharacterAtPosition(char **pcString, int32_t iPosition) {
    int32_t iStringLength, i;
    char *pcReplaceString;

    if(pcString == nullptr || *pcString == nullptr || iPosition < 0 || iPosition >= (iStringLength = strlen(*pcString)))
        return false;

    pcReplaceString = new char[iStringLength];

    for(i = 0; i < iPosition; i ++)
        *(pcReplaceString + i) = *((*pcString) + i);

    for(; i < iStringLength - 1; i ++)
        *(pcReplaceString + i) = *((*pcString) + i + 1);

    *(pcReplaceString + i) = '\0';

    delete[] *pcString;
    *pcString = pcReplaceString;

    return true;
}

bool StringUtility::eraseCharacterAtPosition(wchar_t **pwcString, int32_t iPosition) {
    int32_t iStringLength, i;
    wchar_t *pwcReplaceString;

    if(pwcString == nullptr || *pwcString == nullptr || iPosition < 0 || iPosition >= (iStringLength = wcslen(*pwcString)))
        return false;

    pwcReplaceString = new wchar_t[iStringLength];

    for(i = 0; i < iPosition; i ++)
        *(pwcReplaceString + i) = *((*pwcString) + i);

    for(; i < iStringLength - 1; i ++)
        *(pwcReplaceString + i) = *((*pwcString) + i + 1);

    *(pwcReplaceString + i) = L'\0';

    delete[] *pwcString;
    *pwcString = pwcReplaceString;

    return true;
}

StringUtility* StringUtility::getInstance() {
    if(m_upInstance.get() == nullptr)
        m_upInstance.reset(new StringUtility());

    return m_upInstance.get();
}
