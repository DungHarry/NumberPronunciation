/*
	Author: Dung Ly Viet
	Date created: August 25th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the Number class in C++ programming language
*/

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
	bool bNonZeroGlobal = false;
	int32_t iLevel = 0, iNumberUnitOffset = 0;

	if (this->m_eType != OBJECT_TYPE_NUMBER || this->m_upNumbers.get() == nullptr || this->m_upNumbers->size() <= 0)
		return false;

	this->verifyIgnoreToNumberUnit(this, bNonZeroGlobal, iLevel, iNumberUnitOffset);

	return true;
}

bool Number::verifyIgnoreToNumberUnit(Number *pNumber, bool &bNonZeroGlobal, int32_t &iLevel, int32_t &iNumberUnitOffset) {
	bool bNonZeroLocal = false;
	Number *pNumber;
	Object *pObject;
	int32_t i;
	
	if (pNumber == nullptr || pNumber->getNumbers() == nullptr || pNumber->getNumbers()->size() <= 0)
		return false;

	iLevel ++;
	iNumberUnitOffset ++;

	for (i = pNumber->getNumbers()->size() - 1; i >= 0; i--) {
		if ((pObject = (*(pNumber->getNumbers()->data() + i)).get()) != nullptr) {
			if (pObject->getType() == OBJECT_TYPE_NORMAL_DIGIT) {
				this->verifyIgnoreToObject(pObject, bNonZeroGlobal, bNonZeroLocal, iNumberUnitOffset);
			} else if (pObject->getType() == OBJECT_TYPE_SPECIAL_DIGIT) {
				this->verifyIgnoreToObject(pObject, bNonZeroGlobal, bNonZeroLocal, iNumberUnitOffset);
			} else if (pObject->getType() == OBJECT_TYPE_NUMBER) {
				if ((pNumber = dynamic_cast<Number *>(pObject)) != nullptr)
					this->verifyIgnoreToNumberUnit(pNumber, bNonZeroGlobal, iLevel, iNumberUnitOffset);
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

	for (i = 0; i < pNumber->getNumbers()->size(); i ++) 
		if ((pObject = (*(pNumber->getNumbers()->data() + i)).get()) != NULL && (pDigit = dynamic_cast<Digit *>(pObject)) != NULL && pDigit->getType() == OBJECT_TYPE_NORMAL_DIGIT) {
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