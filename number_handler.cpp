/*
    Author: Dung Ly Viet
    Date created: August 28th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the NumberHandler class in C++ programming language
*/

#include <iostream>
#include "number_handler.h"

unique_ptr<NumberHandler> NumberHandler::m_upInstance (nullptr);

NumberHandler::NumberHandler() :
    Handler (HANDLER_TYPE_NUMBER),
    m_spConfig (nullptr),
    m_upNumber (new Number()),
    m_upNumberString (nullptr)
{

}

NumberHandler::NumberHandler(Config *pConfig, const char *cpcNumberString) :
    Handler (HANDLER_TYPE_NUMBER),
    m_spConfig (pConfig),
    m_upNumber (new Number()),
    m_upNumberString (cpcNumberString == nullptr ? nullptr : new string(cpcNumberString))
{

}

NumberHandler::~NumberHandler() {
    if(this->m_spConfig.get() != nullptr)
        this->m_spConfig.reset();

    if(this->m_upNumber.get() != nullptr)
        this->m_upNumber.reset();

    if(this->m_upNumberString.get() != nullptr)
        this->m_upNumberString.reset();
}

bool NumberHandler::execute() {
    bool bIsSign, bIsFloat;
    char *pcNumericalPart, *pcFloatPart;
    int32_t iNumericalPartLength, iFloatPartLength, iOffset;

    if(this->m_upNumberString.get() == nullptr || this->m_spConfig.get() == nullptr || this->isNumberStringValid() == false) {
        throw NumberException(NUMBER_EXCEPTION_REASON_BAD_FORMAT);

        return false;
    }

    this->m_upNumber.reset(new Number(0));

    this->preprocessStringNumber();

    wcout<<L"PreprocessingString successfully"<<endl;
    wcout<<L"The number string after preprocessing: "<<(this->m_upNumberString->c_str())<<endl;

    bIsSign = this->isNumberStringSign();
    bIsFloat = this->isNumberStringFloat();

    pcNumericalPart = this->getNumberStringNumericalPart();

    wcout<<L"Getting the numerical part successfully"<<endl;

    pcFloatPart = this->getNumberStringFloatingPointPart();

    wcout<<L"Getting the floating point part successfully"<<endl;

    iNumericalPartLength = 0;
    iFloatPartLength = 0;

    if(pcNumericalPart != nullptr) {
        iNumericalPartLength = strlen(pcNumericalPart);

        wcout<<L"Numerical part: "<<pcNumericalPart<<endl;
    }

    if(pcFloatPart != nullptr) {
        iFloatPartLength = strlen(pcFloatPart);

        wcout<<L"Float part: "<<pcFloatPart<<endl;
    }

    iOffset = 0;

    if(bIsSign == true && pcNumericalPart != nullptr)
        this->processSpecialDigit(this->m_upNumberString->at(0));

    wcout<<L"Process special sign digit successfully"<<endl;

	if (pcNumericalPart != nullptr)
		this->processNumberString(pcNumericalPart, iOffset);

    wcout<<L"Process positive numerical string successfully"<<endl;

	if (bIsFloat == true && pcFloatPart != nullptr) {
		this->processSpecialDigit('.');
	
		this->processNumberString(pcFloatPart, 0);
	}

    wcout<<L"Process negative numerical string successfully"<<endl;

	this->m_upNumber->verifyIgnoreToDigits();

    wcout<<L"Verifying to ignore digits successfully"<<endl;

	if (pcNumericalPart != nullptr) 
		delete[] pcNumericalPart;
	
	if (pcFloatPart != nullptr)
		delete[] pcFloatPart;

    wcout<<L"Releasing the bound resources to the system successfully"<<endl;

    return true;
}

Number* NumberHandler::releaseNumber() {
    Number *pNumber;

    if(this->m_upNumber.get() == nullptr)
        return nullptr;

    pNumber = this->m_upNumber.release();

    return pNumber;
}

Config* NumberHandler::getConfig() {
    return this->m_spConfig.get();
}

void NumberHandler::setConfig(Config *pConfig) {
    this->m_spConfig.reset(pConfig);
}

string* NumberHandler::getNumberString() {
    return this->m_upNumberString.get();
}

void NumberHandler::setNumberString(const char *cpcNumberString) {
    this->m_upNumberString.reset(cpcNumberString == nullptr ? nullptr : new string(cpcNumberString));
}

bool NumberHandler::isNumberStringValid() {
    bool bResult, bIsSign = false;
    map<char, int32_t> mSpecialDigitStatistic;
    string::iterator iterChar;
    DigitAttribute *pAttribute;
    set<Container> *pAttributes;
    set<Container>::iterator iterContainer;
    map<char, int32_t>::iterator iterPair;

    if(this->m_upNumberString.get() == nullptr || this->m_spConfig.get() == nullptr)
        return false;

    if((pAttributes = this->m_spConfig->getSpecialDigitAttributes()) != nullptr)
        for(iterContainer = pAttributes->begin(); iterContainer != pAttributes->end(); ++ iterContainer)
            if((pAttribute = dynamic_cast<DigitAttribute *>(iterContainer->getData().get())) != nullptr)
                mSpecialDigitStatistic[pAttribute->getDigit()] = 0;

    if(this->m_upNumberString->at(0) == '-') {
        bIsSign = true;

        mSpecialDigitStatistic['-'] = 1;
    } else if(this->m_upNumberString->at(0) == '+') {
        bIsSign = true;

        mSpecialDigitStatistic['+'] = 1;
    }

    for(bResult = true, iterChar = bIsSign == true ? this->m_upNumberString->begin() + 1 : this->m_upNumberString->begin(); iterChar != this->m_upNumberString->end(); ++ iterChar) {
        if((pAttributes = this->m_spConfig->getNormalDigitAttributes()) != nullptr)
            for(iterContainer = pAttributes->begin(); iterContainer != pAttributes->end(); ++ iterContainer)
                if((pAttribute = dynamic_cast<DigitAttribute *>(iterContainer->getData().get())) != nullptr && pAttribute->getDigit() == *iterChar)
                    break;

        if(iterContainer == pAttributes->end()) {
            if((pAttributes = this->m_spConfig->getSpecialDigitAttributes()) != nullptr)
                for(iterContainer = pAttributes->begin(); iterContainer != pAttributes->end(); ++ iterContainer)
                    if((pAttribute = dynamic_cast<DigitAttribute *>(iterContainer->getData().get())) != nullptr && pAttribute->getDigit() == *iterChar) {
                        if(pAttribute->getDigit() == '-' || pAttribute->getDigit() == '+')
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
    }

    if(bResult == true) {
        for(iterPair = mSpecialDigitStatistic.begin(); iterPair != mSpecialDigitStatistic.end(); ++ iterPair)
            if(iterPair->second > 1) {
                bResult = false;

                break;
            }

        if(bResult == true && mSpecialDigitStatistic['-'] == 1 && mSpecialDigitStatistic['+'] == 1)
            bResult = false;
    }

    mSpecialDigitStatistic.clear();

    return bResult;
}

bool NumberHandler::isNumberStringSign() {
    return (this->m_upNumberString.get() != nullptr && (this->m_upNumberString->at(0) == '-' || this->m_upNumberString->at(0) == '+'));
}

bool NumberHandler::isNumberStringFloat() {
    string::iterator iter;

    if(this->m_upNumberString.get() == nullptr)
        return false;

    for(iter = this->m_upNumberString->begin(); iter != this->m_upNumberString->end(); ++ iter)
        if(*iter == '.')
            break;

    return (iter != this->m_upNumberString->end());
}

NumberHandler* NumberHandler::getInstance() {
	if (m_upInstance.get() == nullptr)
		m_upInstance.reset(new NumberHandler());

	return m_upInstance.get();
}

bool NumberHandler::preprocessStringNumber() {
    bool bIsSign, bIsFloatingPoint;
    int32_t i, iStartIndex, iEndIndex, iOffset;
    char *pcBuffer;

    if(this->isNumberStringValid() == false)
        return false;

    bIsSign = this->isNumberStringSign();
    bIsFloatingPoint = this->isNumberStringFloat();

    iStartIndex = bIsSign == true ? 1 : 0;

    for(; this->m_upNumberString->at(iStartIndex) == '0' && iStartIndex < this->m_upNumberString->size(); ++ iStartIndex);

    if(iStartIndex >= this->m_upNumberString->size()) {
        this->m_upNumberString.reset(new string("0"));

        return true;
    }

    iEndIndex = this->m_upNumberString->size() - 1;

    if(bIsFloatingPoint == true) {
        for(; this->m_upNumberString->at(iEndIndex) == '0' && iEndIndex >= 0; -- iEndIndex);

        if(iEndIndex < 0 || iStartIndex == iEndIndex) {
            this->m_upNumberString.reset(new string("0"));

            return true;
        } else if(this->m_upNumberString->at(iEndIndex) == '.')
            iEndIndex --;
    }

    if(iEndIndex < iStartIndex) {
        this->m_upNumberString.reset(new string("0"));

        return true;
    }

    pcBuffer = new char[iEndIndex - iStartIndex + (bIsSign == true ? 4 : 2)];

    iOffset = 0;

    if(bIsSign == true) {
        *pcBuffer = this->m_upNumberString->at(0);

        if(this->m_upNumberString->at(iStartIndex) == '.') {
            *(pcBuffer + 1) = '0';

            iOffset = 2;
        } else
            iOffset = 1;
    }

    for(i = iStartIndex; i <= iEndIndex; i ++)
        *(pcBuffer + i - iStartIndex + iOffset) = this->m_upNumberString->at(i);

    *(pcBuffer + iEndIndex - iStartIndex + 1 + iOffset) = '\0';

    wcout<<L"The buffer after preprocessing: "<<(pcBuffer)<<endl;

    this->m_upNumberString.reset(new string(pcBuffer));

    delete[] pcBuffer;

    return true;
}

char* NumberHandler::getNumberStringNumericalPart() {
    char *pcResult;
    int32_t iEndIndex, i, j;

    if(this->isNumberStringValid() == false)
        return nullptr;

    iEndIndex = this->m_upNumberString->size() - 1;

    if(this->isNumberStringFloat() == true) {
        for(; this->m_upNumberString->at(iEndIndex) != '.' && iEndIndex >= 0; -- iEndIndex);

        iEndIndex --;
    }

    if(iEndIndex < 0)
        return nullptr;

    pcResult = new char[iEndIndex + 2];

    j = 0;

    if(this->isNumberStringSign())
        j = 1;

    for(i = j; i <= iEndIndex; i ++)
        *(pcResult + i - j) = this->m_upNumberString->at(i);

    *(pcResult + iEndIndex + 1) = '\0';

    return pcResult;
}

char* NumberHandler::getNumberStringFloatingPointPart() {
    char *pcResult;
    int32_t iStartIndex, iEndIndex, i;

    if(this->isNumberStringValid() == false || this->isNumberStringFloat() == false)
        return nullptr;

    iEndIndex = this->m_upNumberString->size() - 1;

    for(iStartIndex = 0; this->m_upNumberString->at(iStartIndex) != '.'; iStartIndex ++);

    iStartIndex ++;

    if(iStartIndex > iEndIndex)
        return nullptr;

    pcResult = new char[iEndIndex - iStartIndex + 2];

    for(i = iStartIndex; i <= iEndIndex; i ++)
        *(pcResult + i - iStartIndex) = this->m_upNumberString->at(i);

    *(pcResult + iEndIndex - iStartIndex + 1) = '\0';

    return pcResult;
}

bool NumberHandler::processSpecialDigit(char cSpecialDigit) {
	Object *pSpecialDigit;

	if (this->m_upNumber.get() == nullptr || this->m_upNumber->getNumbers() == nullptr)
		return false;

	pSpecialDigit = new SpecialDigit(cSpecialDigit, 0);

    this->m_upNumber->getNumbers()->push_back(move(unique_ptr<Object>(pSpecialDigit)));

	return true;
}

bool NumberHandler::processNumberString(const char *cpcNumberString, int32_t iOffset) {
	int32_t i, j, iLevel, iStringLength;
	stack<unique_ptr<Object>> *pNumberStack;
	Number *pNumber;
	NormalDigit *pNormalDigit;

	if (cpcNumberString == nullptr || iOffset < 0 || this->m_upNumber.get() == nullptr || this->m_upNumber->getNumbers() == nullptr)
		return false;

	pNumberStack = new stack<unique_ptr<Object>>();

	iStringLength = strlen(cpcNumberString);

    for (i = iStringLength - 1, iLevel = 0, pNumber = nullptr; i >= iOffset; i--, iLevel ++) {
		if ((j = (iLevel % 3)) == 0) {
			if (iLevel > 0) {
                pNumberStack->push(move(unique_ptr<Object>(pNumber)));
			}

			pNumber = new Number(iLevel);
		}

		pNormalDigit = new NormalDigit(*(cpcNumberString + i), iLevel);

        pNumber->getNumbers()->push_back(move(unique_ptr<Object>(pNormalDigit)));
	}

	if (pNumber != nullptr)
        pNumberStack->push(move(unique_ptr<Object>(pNumber)));

	while (pNumberStack->size() > 0) {
        this->m_upNumber->getNumbers()->push_back(move(pNumberStack->top()));

		pNumberStack->pop();
	}

	delete pNumberStack;

	return true;
}
