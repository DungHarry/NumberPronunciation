/*
    Author: Dung Ly Viet
    Date created: August 28th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the NumberHandler class in C++ programming language
*/

#include "number_handler.h"

auto_ptr<NumberHandler> NumberHandler::m_apInstance (NULL);

NumberHandler::NumberHandler() :
    Handler (HANDLER_TYPE_NUMBER),
    m_spConfig (NULL),
    m_apNumber (new Number()),
    m_apNumberString (NULL)
{

}

NumberHandler::NumberHandler(Config *pConfig, const char *cpcNumberString) :
    Handler (HANDLER_TYPE_NUMBER),
    m_spConfig (pConfig),
    m_apNumber (new Number()),
    m_apNumberString (cpcNumberString == NULL ? NULL : new string(cpcNumberString))
{

}

NumberHandler::~NumberHandler() {
    if(this->m_spConfig.get() != NULL)
        this->m_spConfig.reset();

    if(this->m_apNumber.get() != NULL)
        this->m_apNumber.reset();

    if(this->m_apNumberString.get() != NULL)
        this->m_apNumberString.reset();
}

bool NumberHandler::execute() {
    bool bIsNegative, bIsFloat;
    char *pcNumericalPart, *pcFloatPart;
    int32_t iNumericalPartLength, iFloatPartLength, iOffset, iTmpValue, i;
    Number *pTmpNumber;
    Object *pTmpObject;

    if(this->m_apNumberString.get() == NULL || this->m_spConfig.get() == NULL || this->isNumberStringValid() == false)
        return false;

    this->m_apNumber.reset(new Number(0));

    this->preprocessStringNumber();

    bIsNegative = this->isNumberStringNegative();
    bIsFloat = this->isNumberStringFloat();

    pcNumericalPart = this->getNumberStringNumericalPart();
    pcFloatPart = this->getNumberStringFloatingPointPart();

    iNumericalPartLength = 0;
    iFloatPartLength = 0;

    if(pcNumericalPart != NULL)
        iNumericalPartLength = strlen(pcNumericalPart);

    if(pcFloatPart != NULL)
        iFloatPartLength = strlen(pcFloatPart);

    iOffset = 0;

    if(bIsNegative == true && pcNumericalPart != NULL) {
        pTmpObject = new SpecialDigit('-', 0);

        this->m_apNumber->getNumbers()->push_back(auto_ptr<Object>(pTmpObject));

        iOffset = 1;
    }

    if((iTmpValue = ((iNumericalPartLength - iOffset) % 3)) != 0) {
        pTmpNumber = new Number(iNumericalPartLength - iOffset - iTmpValue);


    }

    return true;
}

Number* NumberHandler::releaseNumber() {
    Number *pNumber;

    if(this->m_apNumber.get() == NULL)
        return NULL;

    pNumber = this->m_apNumber.release();

    return pNumber;
}

Config* NumberHandler::getConfig() {
    return this->m_spConfig.get();
}

void NumberHandler::setConfig(Config *pConfig) {
    this->m_spConfig.reset(pConfig);
}

string* NumberHandler::getNumberString() {
    return this->m_apNumberString.get();
}

void NumberHandler::setNumberString(const char *cpcNumberString) {
    this->m_apNumberString.reset(cpcNumberString == NULL ? NULL : new string(cpcNumberString));
}

bool NumberHandler::isNumberStringValid() {
    bool bResult, bIsNegative;
    map<char, int32_t> mSpecialDigitStatistic;
    string::iterator iterChar;
    DigitAttribute *pAttribute;
    set<Container> *pAttributes;
    set<Container>::iterator iterContainer;
    map<char, int32_t>::iterator iterPair;

    if(this->m_apNumberString.get() == NULL || this->m_spConfig.get() == NULL)
        return false;

    if((pAttributes = this->m_spConfig->getSpecialDigitAttributes()) != NULL)
        for(iterContainer = pAttributes->begin(); iterContainer != pAttributes->end(); ++ iterContainer)
            if((pAttribute = dynamic_cast<DigitAttribute *>(iterContainer->getData().get())) != NULL)
                mSpecialDigitStatistic[pAttribute->getDigit()] = 0;

    if(*(this->m_apNumberString->data()) == '-') {
        bIsNegative = true;

        mSpecialDigitStatistic['-'] = 1;
    }

    for(bResult = true, iterChar = bIsNegative == true ? this->m_apNumberString->begin() + 1 : this->m_apNumberString->begin(); iterChar != this->m_apNumberString->end(); ++ iterChar) {
        if((pAttributes = this->m_spConfig->getNormalDigitAttributes()) != NULL)
            for(iterContainer = pAttributes->begin(); iterContainer != pAttributes->end(); ++ iterContainer)
                if((pAttribute = dynamic_cast<DigitAttribute *>(iterContainer->getData().get())) != NULL && pAttribute->getDigit() == *iterChar)
                    break;

        if(iterContainer == pAttributes->end()) {
            bResult = false;

            break;
        }

        if((pAttributes = this->m_spConfig->getSpecialDigitAttributes()) != NULL)
            for(iterContainer = pAttributes->begin(); iterContainer != pAttributes->end(); ++ iterContainer)
                if((pAttribute = dynamic_cast<DigitAttribute *>(iterContainer->getData().get())) != NULL && pAttribute->getDigit() == *iterChar) {
                    if(pAttribute->getDigit() == '-')
                        bResult = false;

                    mSpecialDigitStatistic[pAttribute->getDigit()] ++;

                    break;
                }

        if(bResult == false)
            break;

        if(iterContainer == pAttributes->end()) {
            bResult = false;

            break;
        }
    }

    if(bResult == true)
        for(iterPair = mSpecialDigitStatistic.begin(); iterPair != mSpecialDigitStatistic.end(); ++ iterPair)
            if(iterPair->second > 1) {
                bResult = false;

                break;
            }

    mSpecialDigitStatistic.clear();

    return bResult;
}

bool NumberHandler::isNumberStringNegative() {
    return (this->isNumberStringValid() && *(this->m_apNumberString->data()) == '-');
}

bool NumberHandler::isNumberStringFloat() {
    string::iterator iter;

    if(this->isNumberStringValid() == false)
        return false;

    for(iter = this->m_apNumberString->begin(); iter != this->m_apNumberString->end(); ++ iter)
        if(*iter == '.')
            break;

    return (iter != this->m_apNumberString->end());
}

bool NumberHandler::preprocessStringNumber() {
    bool bIsNegative, bIsFloatingPoint;
    int32_t i, iStartIndex, iEndIndex, iOffset;
    char *pcBuffer;

    if(this->isNumberStringValid() == false)
        return false;

    bIsNegative = this->isNumberStringNegative();
    bIsFloatingPoint = this->isNumberStringFloat();

    if(bIsNegative == true)
        iStartIndex = 1;

    for(; this->m_apNumberString->at(iStartIndex) == '0' && iStartIndex < this->m_apNumberString->size(); ++ iStartIndex);

    if(iStartIndex >= this->m_apNumberString->size()) {
        this->m_apNumberString.reset(new string("0"));

        return true;
    }

    iEndIndex = this->m_apNumberString->size() - 1;

    if(bIsFloatingPoint == true) {
        for(; this->m_apNumberString->at(iEndIndex) == '0' && iEndIndex >= 0; iEndIndex ++);

        if(iEndIndex < 0 || iStartIndex == iEndIndex) {
            this->m_apNumberString.reset(new string("0"));

            return true;
        } else if(this->m_apNumberString->at(iEndIndex) == '.')
            iEndIndex --;
    }

    if(iEndIndex < iStartIndex) {
        this->m_apNumberString.reset(new string("0"));

        return true;
    }

    pcBuffer = new char[iEndIndex - iStartIndex + (bIsNegative == true ? 4 : 2)];

    iOffset = 0;

    if(bIsNegative == true) {
        *pcBuffer = '-';

        if(this->m_apNumberString->at(iStartIndex) == '.')
            *(pcBuffer + 1) = '0';

        iOffset = 2;
    }

    for(i = iStartIndex; i <= iEndIndex; i ++)
        *(pcBuffer + i - iStartIndex + iOffset) = this->m_apNumberString->at(i);

    *(pcBuffer + iEndIndex - iStartIndex + 1 + iOffset) = '\0';

    this->m_apNumberString.reset(new string(pcBuffer));

    delete[] pcBuffer;

    return true;
}

char* NumberHandler::getNumberStringNumericalPart() {
    char *pcResult;
    int32_t iEndIndex, i;

    if(this->isNumberStringValid() == false)
        return NULL;

    iEndIndex = this->m_apNumberString->size() - 1;

    if(this->isNumberStringFloat() == true) {
        for(; this->m_apNumberString->at(iEndIndex) != '.' && iEndIndex >= 0; -- iEndIndex);

        iEndIndex --;
    }

    if(iEndIndex < 0)
        return NULL;

    pcResult = new char[iEndIndex + 2];

    for(i = 0; i <= iEndIndex; i ++)
        *(pcResult + i) = this->m_apNumberString->at(i);

    *(pcResult + iEndIndex + 1) = '\0';

    return pcResult;
}

char* NumberHandler::getNumberStringFloatingPointPart() {
    char *pcResult;
    int32_t iStartIndex, iEndIndex, i;

    if(this->isNumberStringFloat() == false)
        return NULL;

    iEndIndex = this->m_apNumberString->size() - 1;

    for(iStartIndex = 0; this->m_apNumberString->at(iStartIndex) != '.'; iStartIndex ++);

    iStartIndex ++;

    if(iStartIndex > iEndIndex)
        return false;

    pcResult = new char[iEndIndex - iStartIndex + 2];

    for(i = iStartIndex; i <= iEndIndex; i ++)
        *(pcResult + i - iStartIndex) = this->m_apNumberString->at(i);

    *(pcResult + 1) = '\0';

    return pcResult;
}

bool NumberHandler::processSpecialDigit(char cSpecialDigit) {
	Object *pSpecialDigit;

	if (this->m_apNumber.get() == NULL)
		return false;

	pSpecialDigit = new SpecialDigit(cSpecialDigit, 0);
}

bool NumberHandler::processNumberString(const char *cpcNumberString) {

}