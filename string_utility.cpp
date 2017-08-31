/*
    Author: Dung Ly Viet
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

    if(pcString == nullptr || strlen(pcString) <= 0 || pcResult == nullptr || *pcResult != nullptr)
        return false;

    for(bCommentContain = false, i = 0; i < iStringLength - 1; i ++)
        if(*(pcString + i) == static_cast<char>(0x2F) && *(pcString + i + 1) == static_cast<char>(0x2F)) {
            bCommentContain = true;

            break;
        }

    for(iStartIndex = 0; *(pcString + iStartIndex) == ' '; iStartIndex ++);

    for(iEndIndex = bCommentContain ? i - 1 : iStringLength - 1; *(pcString + iEndIndex) == ' '; iEndIndex --);

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

    if(pwcString == nullptr || wcslen(pwcString) <= 0 || pwcResult == nullptr || *pwcResult != nullptr)
        return false;

    for(bCommentContain = false, i = 0; i < iStringLength - 1; i ++)
        if(*(pwcString + i) == static_cast<wchar_t>(0x2F) && *(pwcString + i + 1) == static_cast<wchar_t>(0x2F)) {
            bCommentContain = true;

            break;
        }

    for(iStartIndex = 0; *(pwcString + iStartIndex) == L' '; iStartIndex ++);

    for(iEndIndex = bCommentContain ? i - 1 : iStringLength - 1; *(pwcString + iEndIndex) == L' '; iEndIndex --);

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
		*(pcResult + i) = ((*(pNumber->getNumbers()->data() + i)).get() == nullptr || (pNormalDigit = dynamic_cast<NormalDigit *>((*(pNumber->getNumbers()->data() + i)).get())) == nullptr) ? '0' : pNormalDigit->getValue();

	*(pcResult + iLength) = '\0';

	return pcResult;
}

StringUtility* StringUtility::getInstance() {
    if(m_upInstance.get() == nullptr)
        m_upInstance.reset(new StringUtility());

    return m_upInstance.get();
}
