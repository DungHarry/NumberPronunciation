/*
	Author: Dung Ly Viet
	Date created: August 25th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the Number class in C++ programming language
*/

#include <iostream>
#include "number.h"

Number::Number() : 
    Object(OBJECT_TYPE_NUMBER),
	m_iLowestUnit(NUMBER_LOWEST_UNIT_INVALID_VALUE),
	m_upNumbers(new vector<unique_ptr<Object>>())
{

}

Number::Number(const int32_t iLowestUnit) :
    Object(OBJECT_TYPE_NUMBER),
	m_iLowestUnit(iLowestUnit < 0 ? NUMBER_LOWEST_UNIT_INVALID_VALUE : iLowestUnit),
	m_upNumbers(new vector<unique_ptr<Object>>())
{

}

Number::~Number() {
	if (this->m_upNumbers.get() != nullptr) {
		this->m_upNumbers->clear();

		this->m_upNumbers.reset();
	}
}

int32_t Number::getLowestUnit() {
	return this->m_iLowestUnit;
}

void Number::setLowestUnit(const int32_t iLowestUnit) {
	if (this->m_iLowestUnit < 0)
		return;

	this->m_iLowestUnit = iLowestUnit;
}

vector<unique_ptr<Object>>* Number::getNumbers() {
	return this->m_upNumbers.get();
}

bool Number::verifyIgnoreToDigits() {
    bool bNonZeroGlobal = false, bResult;
	int32_t iLevel = 0, iNumberUnitOffset = 0;

	if (this->m_eType != OBJECT_TYPE_NUMBER || this->m_upNumbers.get() == nullptr || this->m_upNumbers->size() <= 0)
		return false;

    wcout<<L"Inside the verifying to ignore the digits"<<endl;

    bResult = this->verifyIgnoreToNumberUnit(this, bNonZeroGlobal, iLevel, iNumberUnitOffset);
    bResult &= this->verifyIgnoreToFloatingPointPart(this);

    wcout<<L"Completing the verify process to ignore the digits"<<endl;

    return bResult;
}

bool Number::verifyIgnoreToFloatingPointPart(Number *pNumber) {
    int32_t iIndexDot;
    Object *pObject;
    Digit *pDigit;
    bool bNonZero = false;

    if(pNumber == nullptr || pNumber->getNumbers() == nullptr || pNumber->getNumbers()->size() <= 0)
        return false;

    for(iIndexDot = 0; iIndexDot < pNumber->getNumbers()->size(); iIndexDot ++)
        if((pObject = pNumber->getNumbers()->at(iIndexDot).get()) != nullptr && pObject->getType() == OBJECT_TYPE_SPECIAL_DIGIT && (pDigit = dynamic_cast<Digit *>(pObject)) != nullptr && pDigit->getValue() == '.')
            break;

    if(iIndexDot >= pNumber->getNumbers()->size())
        return true;

    for(iIndexDot ++; iIndexDot < pNumber->getNumbers()->size() && bNonZero == false; iIndexDot ++)
        if((pObject = pNumber->getNumbers()->at(iIndexDot).get()) != nullptr)
            this->verifyIgnoreToFloatingPointPart(pObject, bNonZero);

    return true;
}

bool Number::verifyIgnoreToFloatingPointPart(Object *pObject, bool &bNonZero) {
    Digit *pDigit;
    Object *pTmpObject;
    Number *pNumber;
    int32_t i;

    if(pObject == nullptr || bNonZero == true)
        return false;

    if(pObject->getType() == OBJECT_TYPE_NORMAL_DIGIT && (pDigit = dynamic_cast<Digit *>(pObject)) != nullptr) {
        if(pDigit->getValue() != '0') {
            bNonZero = true;

            return true;
        }

        pDigit->setIgnore(false);
    } else if(pObject->getType() == OBJECT_TYPE_NUMBER && (pNumber = dynamic_cast<Number *>(pObject)) != nullptr && pNumber->getNumbers() != nullptr && pNumber->getNumbers()->size() <= 0)
        for(i = 0; i < pNumber->getNumbers()->size() && bNonZero == false; i ++)
            if((pTmpObject = pNumber->getNumbers()->at(i).get()) != nullptr)
                this->verifyIgnoreToFloatingPointPart(pTmpObject, bNonZero);

    return true;
}

bool Number::verifyIgnoreToNumberUnit(Number *pNumber, bool &bNonZeroGlobal, int32_t iLevel, int32_t &iNumberUnitOffset) {
    Number *pTmpNumber;
    bool bNonZeroLocal = false;
	Object *pObject;
    NormalDigit *pNormalDigit;
	int32_t i;
	
	if (pNumber == nullptr || pNumber->getNumbers() == nullptr || pNumber->getNumbers()->size() <= 0)
		return false;


	iNumberUnitOffset ++;

    if(this->isAllThreeZeroDigits(pNumber) == true && pNumber->getNumbers() != nullptr && pNumber->getNumbers()->size() == 3) {
        wcout<<"Inside three zero digit"<<endl;

        for(i = 0; i < pNumber->getNumbers()->size(); i ++)
            if((pNormalDigit = dynamic_cast<NormalDigit *>(pNumber->getNumbers()->at(i).get())) != nullptr && pNormalDigit->getValue() == '0')
                pNormalDigit->setIgnore(true);
            else
                break;

        if(i >= pNumber->getNumbers()->size())
            return true;
    }

    iLevel ++;

    wcout<<L"Size of the numbers: "<<(pNumber->getNumbers()->size())<<endl;

	for (i = pNumber->getNumbers()->size() - 1; i >= 0; i--) {
        wcout<<L"Executing "<<i<<L"..."<<endl;

        if ((pObject = pNumber->getNumbers()->at(i).get()) != nullptr) {
			if (pObject->getType() == OBJECT_TYPE_NORMAL_DIGIT) {
                wcout<<L"Case of normal digit"<<endl;

				this->verifyIgnoreToObject(pObject, bNonZeroGlobal, bNonZeroLocal, iNumberUnitOffset);
			} else if (pObject->getType() == OBJECT_TYPE_SPECIAL_DIGIT) {
                wcout<<L"Case of special digit"<<endl;

                this->verifyIgnoreToObject(pObject, bNonZeroGlobal, bNonZeroLocal, iNumberUnitOffset);
			} else if (pObject->getType() == OBJECT_TYPE_NUMBER) {
                wcout<<L"Case of number"<<endl;

                if ((pTmpNumber = dynamic_cast<Number *>(pObject)) != nullptr)
                    this->verifyIgnoreToNumberUnit(pTmpNumber, bNonZeroGlobal, iLevel, iNumberUnitOffset);
			}
		}
	}

	if (iLevel == 2 && iNumberUnitOffset >= 3 && bNonZeroGlobal == true && bNonZeroLocal == true) 
		this->verifyIgnoreToNumberUnitAgain(pNumber);

	iLevel --;

	return true;
}

bool Number::verifyIgnoreToObject(Object *pObject, bool &bNonZeroGlobal, bool &bNonZeroLocal, int32_t &iNumberUnitOffset) {
	Digit *pDigit;

	if (pObject == NULL || (pObject->getType() != OBJECT_TYPE_NORMAL_DIGIT && pObject->getType() != OBJECT_TYPE_SPECIAL_DIGIT) || (pDigit = dynamic_cast<Digit *>(pObject)) == nullptr)
		return false;
	
	if(pObject->getType() == OBJECT_TYPE_NORMAL_DIGIT) {
		if (pDigit->getValue() != '0') {
			bNonZeroGlobal = true;
			bNonZeroLocal = true;
		} else if (bNonZeroGlobal == true && bNonZeroLocal == true)
			pDigit->setIgnore(true);
	} else if (pDigit->getValue() == '.') {
		bNonZeroGlobal = false;
		bNonZeroLocal = false;
		iNumberUnitOffset = 1;

        return false;
	}

	return true;
}

bool Number::verifyIgnoreToNumberUnitAgain(Number *pNumber) {
	int32_t i;
	Object *pObject;
	Digit *pDigit;
	bool bNonZero = false;

	if (pNumber == NULL || pNumber->getNumbers() == NULL || pNumber->getNumbers()->size() <= 0)
		return false;

    wcout<<L"Inside verifying to number again"<<endl;

	for (i = 0; i < pNumber->getNumbers()->size(); i ++) 
        if ((pObject = pNumber->getNumbers()->at(i).get()) != NULL && (pDigit = dynamic_cast<Digit *>(pObject)) != NULL && pDigit->getType() == OBJECT_TYPE_NORMAL_DIGIT) {
			if (bNonZero == false) {
				if (pDigit->getValue() == '0') {
					if (pDigit->getIgnore() == false)
						pDigit->setIgnore(true);
				} else 
					bNonZero = true;
						
			} else {
				if (pDigit->getValue() == '0' && pDigit->getIgnore() == true)
					pDigit->setIgnore(false);
			}
		}

	return true;
}

bool Number::isAllThreeZeroDigits(Number *pNumber) {
    NormalDigit *pNormalDigit;

    return (pNumber != nullptr && pNumber->getNumbers() != nullptr && pNumber->getNumbers()->size() == 3 && pNumber->getNumbers()->at(0).get() != nullptr && pNumber->getNumbers()->at(0)->getType() == OBJECT_TYPE_NORMAL_DIGIT && (pNormalDigit = dynamic_cast<NormalDigit *>(pNumber->getNumbers()->at(0).get())) != nullptr && pNormalDigit->getValue() == '0' && pNumber->getNumbers()->at(1).get() != nullptr && pNumber->getNumbers()->at(1)->getType() == OBJECT_TYPE_NORMAL_DIGIT && (pNormalDigit = dynamic_cast<NormalDigit *>(pNumber->getNumbers()->at(1).get())) != nullptr && pNormalDigit->getValue() == '0' && pNumber->getNumbers()->at(2).get() != nullptr && pNumber->getNumbers()->at(2)->getType() == OBJECT_TYPE_NORMAL_DIGIT && (pNormalDigit = dynamic_cast<NormalDigit *>(pNumber->getNumbers()->at(2).get())) != nullptr && pNormalDigit->getValue() == '0');
}
