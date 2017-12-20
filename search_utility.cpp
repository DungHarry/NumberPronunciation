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
	Date created: August 30th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the SearchUtility class in C++ programming language
*/

#include "search_utility.h"

unique_ptr<SearchUtility> SearchUtility::m_upInstance (nullptr);

SearchUtility::SearchUtility() :
	Utility(UTILITY_TYPE_SEARCH)
{

}

SearchUtility::~SearchUtility() {

}

Comparable* SearchUtility::find(const set<Container> *pSet, const Container &con) {
	set<Container>::iterator iter;

	if (pSet == nullptr)
		return nullptr;

	iter = pSet->find(con);

	return (iter == pSet->end()) ? nullptr : iter->getData().get();
}

Comparable* SearchUtility::find(const set<Container> *pSet, int16_t iPosition) {
	set<Container>::iterator iter;
    shared_ptr<Comparable> spConditionAppendAttribute (nullptr);

	if (pSet == nullptr)
		return nullptr;

    spConditionAppendAttribute.reset(new ConditionAppendAttribute(0, iPosition, nullptr));

    iter = pSet->find(Container(spConditionAppendAttribute));

    spConditionAppendAttribute.reset();

	return (iter == pSet->end()) ? nullptr : iter->getData().get();
}

Comparable* SearchUtility::find(const set<Container> *pSet, char cDigit) {
	set<Container>::iterator iter;
    shared_ptr<Comparable> spDigitAttribute (nullptr);

	if (pSet == nullptr)
		return nullptr;

    spDigitAttribute.reset(new DigitAttribute(ATTRIBUTE_TYPE_NORMAL_DIGIT, 0, cDigit, nullptr));

    iter = pSet->find(Container(spDigitAttribute));

    spDigitAttribute.reset();

	return (iter == pSet->end()) ? nullptr : iter->getData().get();
}

Comparable* SearchUtility::find(const set<Container> *pSet, const wchar_t *cpwcMultipleDigits) {
	set<Container>::iterator iter;
    shared_ptr<Comparable> spMultipleDigitAttribute;

	if (pSet == nullptr || cpwcMultipleDigits == nullptr)
		return nullptr;

    spMultipleDigitAttribute.reset(new MultipleDigitsAttribute(0, cpwcMultipleDigits, nullptr));

    iter = pSet->find(Container(spMultipleDigitAttribute));

    spMultipleDigitAttribute.reset();

	return (iter == pSet->end()) ? nullptr : iter->getData().get();
}

Comparable* SearchUtility::find(const set<Container> *pSet, char cDigit, int16_t iPosition) {
	set<Container>::iterator iter;
    ConditionDigitAttribute *pConditionDigitAttribute;
    shared_ptr<Comparable> spConditionDigitAttribute;

	if (pSet == nullptr || iPosition < 0)
		return nullptr;

    spConditionDigitAttribute.reset(new ConditionDigitAttribute(iPosition, 0, cDigit, nullptr));

    iter = pSet->find(Container(spConditionDigitAttribute));

    spConditionDigitAttribute.reset();

	return (iter == pSet->end() || iter->getData().get() == nullptr || (pConditionDigitAttribute = dynamic_cast<ConditionDigitAttribute *>(iter->getData().get())) == nullptr || pConditionDigitAttribute->getPosition() != iPosition) ? nullptr : iter->getData().get();
}

Comparable* SearchUtility::find(const set<Container> *pSet, int16_t iPosition, const wchar_t *cpwcEndDigits) {
    set<Container>::iterator iter;
    shared_ptr<Comparable> spConditionAppendDigitsEndAttribute;

    if(pSet == nullptr || iPosition < 0 || cpwcEndDigits == nullptr)
        return nullptr;

    spConditionAppendDigitsEndAttribute.reset(new ConditionAppendDigitsEndAttribute(0, iPosition, cpwcEndDigits, nullptr));

    iter = pSet->find(Container(spConditionAppendDigitsEndAttribute));

    spConditionAppendDigitsEndAttribute.reset();

    return (iter == pSet->end()) ? nullptr : iter->getData().get();
}

SearchUtility* SearchUtility::getInstance() {
	if (m_upInstance.get() == nullptr)
		m_upInstance.reset(new SearchUtility());

	return m_upInstance.get();
}
