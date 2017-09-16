/*
	Author: Dung Ly Viet
	Date created: August 29th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the PronunciationHandler class in C++ programming language
*/

#include "pronunciation_handler.h"

unique_ptr<PronunciationHandler> PronunciationHandler::m_upInstance (nullptr);

PronunciationHandler::PronunciationHandler() :
	Handler (HANDLER_TYPE_PRONUNCIATION)
{

}

PronunciationHandler::PronunciationHandler(Config *pConfig, Number *pNumber) :
	Handler (HANDLER_TYPE_PRONUNCIATION),
	m_upConfig (pConfig),
	m_upNumber (pNumber)
{

}

PronunciationHandler::~PronunciationHandler() {
	if (this->m_upConfig.get() != nullptr)
		this->m_upConfig.release();

	if (this->m_upNumber.get() != nullptr)
		this->m_upConfig.release();

	if (this->m_upwsPronunciation.get() != nullptr)
		this->m_upwsPronunciation.release();
}

bool PronunciationHandler::execute() {
	int32_t i;
	vector<unique_ptr<Object>> *pNumbers;
	PronunciationHandlerState eState;

	if (this->m_upConfig.get() == nullptr || this->m_upNumber.get() == nullptr || (pNumbers = this->m_upNumber->getNumbers()) == nullptr)
		return false;

    this->m_upwsPronunciation.reset(new wstring());

    for (i = 0; i < pNumbers->size(); i ++)
        if (pNumbers->at(i).get() != nullptr) {
            eState = this->detectExecutionState(pNumbers->at(i).get());

            if (this->processState(eState, pNumbers->at(i).get(), 0, 0) == false)
				return false;
		}

	return true;
}

Config* PronunciationHandler::getConfig() {
	return this->m_upConfig.get(); 
}

void PronunciationHandler::setConfig(Config *pConfig) {
	this->m_upConfig.reset(pConfig);
}

Number* PronunciationHandler::getNumber() {
	return this->m_upNumber.get();
}

void PronunciationHandler::setNumber(Number *pNumber) {
	this->m_upNumber.reset(pNumber);
}

wstring* PronunciationHandler::getPronunciation() {
	return this->m_upwsPronunciation.get();
}

wstring* PronunciationHandler::releasePronunciation() {
    return this->m_upwsPronunciation.release();
}

PronunciationHandler* PronunciationHandler::getInstance() {
	if (m_upInstance.get() == nullptr)
		m_upInstance.reset(new PronunciationHandler());

	return m_upInstance.get();
}

PronunciationHandlerState PronunciationHandler::detectExecutionState(Object *pObject) {
	ObjectType eObjectType;
	PronunciationHandlerState eStateResult;
	
	if (pObject == nullptr)
		return PRONUNCIATION_HANDLER_STATE_NONE;

	if ((eObjectType = pObject->getType()) == OBJECT_TYPE_NORMAL_DIGIT)
		eStateResult = PRONUNCIATION_HANDLER_STATE_NORMAL_DIGIT;
	else if (eObjectType == OBJECT_TYPE_SPECIAL_DIGIT)
		eStateResult = PRONUNCIATION_HANDLER_STATE_SPECIAL_DIGIT;
	else if (eObjectType == OBJECT_TYPE_NUMBER)
		eStateResult = PRONUNCIATION_HANDLER_STATE_NUMBER_UNIT;
	else
		eStateResult = PRONUNCIATION_HANDLER_STATE_NONE;

	return eStateResult;
}

bool PronunciationHandler::processState(const PronunciationHandlerState eState, Object *pObject, int32_t iLength, int32_t iUnit) {
	NormalDigit *pNormalDigit = nullptr;
	SpecialDigit *pSpecialDigit;
	Number *pNumber;
	PronunciationHandlerState eObjectState;
    char *pcNumber, cDigit;

	if (pObject == nullptr || eState <= PRONUNCIATION_HANDLER_STATE_NONE || eState >= PRONUNCIATION_HANDLER_STATE_COUNT)
		return false;

	if (eState == PRONUNCIATION_HANDLER_STATE_NORMAL_DIGIT) {
        if ((pNormalDigit = dynamic_cast<NormalDigit *>(pObject)) == nullptr)
            return false;

        if(pNormalDigit->getIgnore() == true)
            return true;

        if(this->pronounceNormalDigit(pNormalDigit->getValue()) == false)
            return false;
	} else if (eState == PRONUNCIATION_HANDLER_STATE_SPECIAL_DIGIT) {
        if ((pSpecialDigit = dynamic_cast<SpecialDigit *>(pObject)) == nullptr || pSpecialDigit->getIgnore() == true)
			return false;

        if (pSpecialDigit->getIgnore() == false && this->pronounceSpecialDigit(pSpecialDigit->getValue()) == false)
			return false;
	} else if (eState == PRONUNCIATION_HANDLER_STATE_NUMBER_UNIT) {
		if ((pNumber = dynamic_cast<Number*>(pObject)) == nullptr)
			return false;

		if (this->processNumberUnit(pNumber) == false)
			return false;
	} else if (eState == PRONUNCIATION_HANDLER_STATE_CONDITION_APPEND) {
		if (this->pronounceConditionAppend(iUnit) == false)
			return false;
	} else if (eState == PRONUNCIATION_HANDLER_STATE_CONDITION_DIGIT) {
        if ((eObjectState = this->detectExecutionState(pObject)) != PRONUNCIATION_HANDLER_STATE_NORMAL_DIGIT || (pNormalDigit = dynamic_cast<NormalDigit *>(pObject)) == nullptr || pNormalDigit->getIgnore() == false || this->pronounceConditionDigit(pNormalDigit->getValue(), iUnit) == false)
			return false;
	} else if (eState == PRONUNCIATION_HANDLER_STATE_MULTIPLE_DIGITS) {
		pcNumber = nullptr;

		if (iLength <= 0 || StringUtility::getInstance() == nullptr || (pNumber = dynamic_cast<Number *>(pObject)) == nullptr || (pcNumber = StringUtility::getInstance()->getSubStringNumber(pNumber, iLength)) == nullptr || this->pronounceMutipleDigits(pcNumber) == false) {
			if (pcNumber != nullptr)
				delete[] pcNumber;
			
			return false;
		}

		if (pcNumber != nullptr)
			delete[] pcNumber;
    } else if(eState == PRONUNCIATION_HANDLER_STATE_MULTIPLE_DIGITS_WITH_ZERO_APPENDED) {
        if(StringUtility::getInstance() == nullptr || (pNumber = dynamic_cast<Number *>(pObject)) == nullptr || (cDigit = StringUtility::getInstance()->getCharacterNumber(pNumber, iUnit)) == '\0' || this->pronounceMutipleDigitsWithZeroAppended(cDigit, iUnit) == false)
            return false;
    }

	return true;
}

bool PronunciationHandler::pronounceSpecialDigit(const char cDigit) {
	Comparable *pResult;
	SpecialDigitAttribute *pSpecialDigitAttribute;
	unique_ptr<wstring> upTmpPronunciation;

    if (this->m_upConfig.get() == nullptr || this->m_upConfig->getSpecialDigitAttributes() == nullptr || this->m_upwsPronunciation.get() == nullptr || SearchUtility::getInstance() == nullptr)
        return false;

    if ((pResult = SearchUtility::getInstance()->find(this->m_upConfig->getSpecialDigitAttributes(), cDigit)) == nullptr || (pSpecialDigitAttribute = dynamic_cast<SpecialDigitAttribute *>(pResult)) == nullptr || pSpecialDigitAttribute->getPronunciation() == nullptr)
        return false;

	upTmpPronunciation.reset(new wstring(pSpecialDigitAttribute->getPronunciation()));

	upTmpPronunciation->append(L" ");

	this->m_upwsPronunciation->append(upTmpPronunciation->c_str());

	upTmpPronunciation.reset();

	return true;
}

bool PronunciationHandler::processNumberUnit(Number *pNumber) {
	int32_t i;
	PronunciationHandlerState eState;
	Object *pObject;
	
	if (pNumber == nullptr || pNumber->getNumbers() == nullptr || this->m_upConfig.get() == nullptr || this->m_upwsPronunciation.get() == nullptr)
		return false;

    for (i = pNumber->getNumbers()->size() - 1; i >= 0; i --)
        if ((pObject = pNumber->getNumbers()->at(i).get()) != nullptr && (eState = this->detectExecutionState(pObject)) == PRONUNCIATION_HANDLER_STATE_NUMBER_UNIT)
			this->processState(eState, pObject, 0, i);

	if (this->handleNumberUnitNumDigits(pNumber, pNumber->getNumbers()->size()) == false)
		return false;

	return this->processState(PRONUNCIATION_HANDLER_STATE_CONDITION_APPEND, pNumber, 0, pNumber->getLowestUnit());
}

bool PronunciationHandler::handleNumberUnitNumDigits(Number *pNumber, int32_t iNumDigits) {
	PronunciationHandlerState eState;
	Object *pObject;
	unique_ptr<string> upBuffer;
	int32_t i;
	vector<unique_ptr<Object>> *pNumberObjects;
	Config *pConfig;
    NormalDigit *pNormalDigit;

	if (pNumber == nullptr || (pNumberObjects = pNumber->getNumbers()) == nullptr || (pConfig = this->m_upConfig.get()) == nullptr || this->m_upwsPronunciation.get() == nullptr)
		return false;

	if (iNumDigits == 3) {
        if(this->processState(PRONUNCIATION_HANDLER_STATE_MULTIPLE_DIGITS_WITH_ZERO_APPENDED, pNumber, 3, 2) == false) {
            if (this->processState(PRONUNCIATION_HANDLER_STATE_MULTIPLE_DIGITS, pNumber, 3, 2) == false) {
                if ((pObject = (*(pNumberObjects->data() + 2)).get()) == nullptr)
                    return false;

                if ((eState = this->detectExecutionState(pObject)) == PRONUNCIATION_HANDLER_STATE_NORMAL_DIGIT) {
                    if((pNormalDigit = dynamic_cast<NormalDigit *>(pObject)) == nullptr)
                        return false;

                    if (pNormalDigit->getIgnore() == false && this->processState(PRONUNCIATION_HANDLER_STATE_CONDITION_DIGIT, pObject, 3, 2) == false) {
                        if ((pNormalDigit = dynamic_cast<NormalDigit *>(pObject)) == nullptr || this->processState(eState, pObject, 3, 2) == false)
                            return false;

                        this->processState(PRONUNCIATION_HANDLER_STATE_CONDITION_APPEND, pObject, 3, 2);
                    }
                } else if (eState == PRONUNCIATION_HANDLER_STATE_SPECIAL_DIGIT) {
                    if (this->processState(eState, pObject, 3, 2) == false)
                        return false;
                }

                this->handleNumberUnitNumDigits(pNumber, 2);
            }
        } else
            this->handleNumberUnitNumDigits(pNumber, 2);
	} else if (iNumDigits == 2) {
        if(this->processState(PRONUNCIATION_HANDLER_STATE_MULTIPLE_DIGITS_WITH_ZERO_APPENDED, pNumber, 2, 1) == false) {
            if (this->processState(PRONUNCIATION_HANDLER_STATE_MULTIPLE_DIGITS, pNumber, 2, 1) == false) {
                if ((pObject = (*(pNumberObjects->data() + 1)).get()) == nullptr)
                    return false;

                if ((eState = this->detectExecutionState(pObject)) == PRONUNCIATION_HANDLER_STATE_NORMAL_DIGIT) {
                    if((pNormalDigit = dynamic_cast<NormalDigit *>(pObject)) == nullptr)
                        return false;

                    if (pNormalDigit->getIgnore() == false && this->processState(PRONUNCIATION_HANDLER_STATE_CONDITION_DIGIT, pObject, 2, 1) == false) {
                        if ((pNormalDigit = dynamic_cast<NormalDigit *>(pObject)) == nullptr || this->processState(eState, pObject, 2, 1) == false)
                            return false;

                        this->processState(PRONUNCIATION_HANDLER_STATE_CONDITION_APPEND, pObject, 2, 1);
                    }
                } else if (eState == PRONUNCIATION_HANDLER_STATE_SPECIAL_DIGIT) {
                    if (this->processState(eState, pObject, 2, 1) == false)
                        return false;
                }

                this->handleNumberUnitNumDigits(pNumber, 1);
            }
        } else
            this->handleNumberUnitNumDigits(pNumber, 1);
	} else if (iNumDigits == 1) {
        if ((pObject = (*(pNumberObjects->data() + 0)).get()) == nullptr)
            return false;

		if ((eState = this->detectExecutionState(pObject)) == PRONUNCIATION_HANDLER_STATE_NORMAL_DIGIT) {
            if((pNormalDigit = dynamic_cast<NormalDigit *>(pObject)) == nullptr)
                return false;

            if (pNormalDigit->getIgnore() == false && this->processState(PRONUNCIATION_HANDLER_STATE_CONDITION_DIGIT, pObject, 1, 0) == false) {
                if (this->processState(eState, pObject, 1, 0) == false)
					return false;

                    this->processState(PRONUNCIATION_HANDLER_STATE_CONDITION_APPEND, pObject, 1, 0);
			}
		} else if (eState == PRONUNCIATION_HANDLER_STATE_SPECIAL_DIGIT) {
			if (this->processState(eState, pObject, 1, 0) == false)
				return false;
		}
	}

	return true;
}

bool PronunciationHandler::pronounceMutipleDigits(const char *cpcMultipleDigits) {
	Comparable *pComparable;
	MultipleDigitsAttribute *pMultipleDigitsAttribute;
	wchar_t *pwcMultipleDigits;
	unique_ptr<wstring> upTmpPronunciation;

    if (cpcMultipleDigits == nullptr || this->m_upConfig.get() == nullptr || this->m_upConfig->getMultipleDigitsAttributes() == nullptr || StringUtility::getInstance() == nullptr || SearchUtility::getInstance() == nullptr || this->m_upwsPronunciation.get() == nullptr)
		return false;

	if ((pwcMultipleDigits = StringUtility::getInstance()->convertToWChar(cpcMultipleDigits)) == nullptr)
		return false;

    if ((pComparable = SearchUtility::getInstance()->find(this->m_upConfig->getMultipleDigitsAttributes(), pwcMultipleDigits)) == nullptr || (pMultipleDigitsAttribute = dynamic_cast<MultipleDigitsAttribute *>(pComparable)) == nullptr || pMultipleDigitsAttribute->getPronunciation() == nullptr) {
        delete[] pwcMultipleDigits;
		
		return false;
	}

	upTmpPronunciation.reset(new wstring(pMultipleDigitsAttribute->getPronunciation()));

	upTmpPronunciation->append(L" ");

	this->m_upwsPronunciation->append(upTmpPronunciation->c_str());

	upTmpPronunciation.reset();

	delete[] pwcMultipleDigits;
	
	return true;
}

bool PronunciationHandler::pronounceMutipleDigitsWithZeroAppended(char cDigit, int32_t iUnit) {
    Comparable *pComparable;
    MultipleDigitsAttribute *pMultipleDigitsAttribute;
    wchar_t *pwcMultipleDigits;
    unique_ptr<wstring> upTmpPronunciation;

    if(this->m_upConfig.get() == nullptr || this->m_upConfig->getMultipleDigitsAttributes() == nullptr || StringUtility::getInstance() == nullptr || SearchUtility::getInstance() == nullptr || this->m_upwsPronunciation.get() == nullptr || iUnit <= 0)
        return false;

    if((pwcMultipleDigits = StringUtility::getInstance()->appendZero(static_cast<wchar_t>(cDigit), iUnit)) == nullptr)
        return false;

    if((pComparable = SearchUtility::getInstance()->find(this->m_upConfig->getMultipleDigitsAttributes(), pwcMultipleDigits)) == nullptr || (pMultipleDigitsAttribute = dynamic_cast<MultipleDigitsAttribute *>(pComparable)) == nullptr || pMultipleDigitsAttribute->getPronunciation() == nullptr) {
        delete[] pwcMultipleDigits;

        return false;
    }

    upTmpPronunciation.reset(new wstring(pMultipleDigitsAttribute->getPronunciation()));

    upTmpPronunciation->append(L" ");

    this->m_upwsPronunciation->append(upTmpPronunciation->c_str());

    upTmpPronunciation.reset();

    delete[] pwcMultipleDigits;

    return true;
}

bool PronunciationHandler::pronounceConditionDigit(const char cDigit, const int16_t iDigitPosition) {
	Comparable *pComparable;
	ConditionDigitAttribute *pConditionDigitAttribute;
	unique_ptr<wstring> upTmpPronunciation;

	if (iDigitPosition < 0 || this->m_upConfig.get() == nullptr || this->m_upConfig->getConditionDigitAttributes() == nullptr || this->m_upwsPronunciation.get() == nullptr || SearchUtility::getInstance() == nullptr)
		return false;

	if ((pComparable = SearchUtility::getInstance()->find(this->m_upConfig->getConditionDigitAttributes(), cDigit, iDigitPosition)) == nullptr || (pConditionDigitAttribute = dynamic_cast<ConditionDigitAttribute*>(pComparable)) == nullptr)
		return false;

	upTmpPronunciation.reset(new wstring(pConditionDigitAttribute->getPronunciation()));
	upTmpPronunciation->append(L" ");

	this->m_upwsPronunciation->append(upTmpPronunciation->c_str());

	upTmpPronunciation.reset();

	return true;
}

bool PronunciationHandler::pronounceNormalDigit(const char cDigit) {
	Comparable *pComparable;
	NormalDigitAttribute *pNormalDigitAttribute;
	unique_ptr<wstring> upTmpPronunciation;

	if (this->m_upConfig.get() == nullptr || this->m_upConfig->getNormalDigitAttributes() == nullptr || this->m_upwsPronunciation.get() == nullptr || SearchUtility::getInstance() == nullptr)
		return false;

	if ((pComparable = SearchUtility::getInstance()->find(this->m_upConfig->getNormalDigitAttributes(), cDigit)) == nullptr || (pNormalDigitAttribute = dynamic_cast<NormalDigitAttribute *>(pComparable)) == nullptr)
		return false;

	upTmpPronunciation.reset(new wstring(pNormalDigitAttribute->getPronunciation()));
	upTmpPronunciation->append(L" ");

	this->m_upwsPronunciation->append(upTmpPronunciation->c_str());

	upTmpPronunciation.reset();

	return true;
}

bool PronunciationHandler::pronounceConditionAppend(const int16_t iDigitPosition) {
	Comparable *pComparable;
	ConditionAppendAttribute *pConditionAppendAttribute;
	unique_ptr<wstring> upTmpPronunciation;

    if (iDigitPosition < 0 || this->m_upConfig.get() == nullptr || this->m_upConfig->getConditionAppendAttributes() == nullptr || this->m_upwsPronunciation.get() == nullptr || SearchUtility::getInstance() == nullptr)
        return false;

    if((pComparable = SearchUtility::getInstance()->find(this->m_upConfig->getConditionAppendAttributes(), iDigitPosition)) == nullptr)
        return true;

    if ((pConditionAppendAttribute = dynamic_cast<ConditionAppendAttribute *>(pComparable)) == nullptr)
        return false;

	upTmpPronunciation.reset(new wstring(pConditionAppendAttribute->getPronunciation()));
	upTmpPronunciation->append(L" ");

	this->m_upwsPronunciation->append(upTmpPronunciation->c_str());

	upTmpPronunciation.reset();

	return true;
}
