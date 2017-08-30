/*
	Author: Dung Ly Viet
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
	ConditionAppendAttribute *pConditionAppendAttribute;

	if (pSet == nullptr)
		return nullptr;

	pConditionAppendAttribute = new ConditionAppendAttribute(0, iPosition, nullptr);

	iter = pSet->find(Container(shared_ptr<Comparable>(pConditionAppendAttribute)));

	return (iter == pSet->end()) ? nullptr : iter->getData().get();
}

Comparable* SearchUtility::find(const set<Container> *pSet, char cDigit) {
	set<Container>::iterator iter;
	DigitAttribute *pDigitAttribute;

	if (pSet == nullptr)
		return nullptr;

	pDigitAttribute = new DigitAttribute(ATTRIBUTE_TYPE_NORMAL_DIGIT, 0, cDigit, nullptr);

	iter = pSet->find(Container(shared_ptr<Comparable>(pDigitAttribute)));

	return (iter == pSet->end()) ? nullptr : iter->getData().get();
}

Comparable* SearchUtility::find(const set<Container> *pSet, const wchar_t *cpwcMultipleDigits) {
	set<Container>::iterator iter;
	MultipleDigitsAttribute *pMultipleDigitAttribute;

	if (pSet == nullptr || cpwcMultipleDigits == nullptr)
		return nullptr;

	pMultipleDigitAttribute = new MultipleDigitsAttribute(0, cpwcMultipleDigits, nullptr);

	iter = pSet->find(Container(shared_ptr<Comparable>(pMultipleDigitAttribute)));

	return (iter == pSet->end()) ? nullptr : iter->getData().get();
}

Comparable* SearchUtility::find(const set<Container> *pSet, char cDigit, int16_t iPosition) {
	set<Container>::iterator iter;
	ConditionDigitAttribute *pConditionDigitAttribute;

	if (pSet == nullptr || iPosition < 0)
		return nullptr;

	pConditionDigitAttribute = new ConditionDigitAttribute(iPosition, 0, cDigit, nullptr);

	iter = pSet->find(Container(shared_ptr<Comparable>(pConditionDigitAttribute)));

	return (iter == pSet->end() || iter->getData().get() == nullptr || (pConditionDigitAttribute = dynamic_cast<ConditionDigitAttribute *>(iter->getData().get())) == nullptr || pConditionDigitAttribute->getPosition() != iPosition) ? nullptr : iter->getData().get();
}

SearchUtility* SearchUtility::getInstance() {
	if (m_upInstance.get() == nullptr)
		m_upInstance.reset(new SearchUtility());

	return m_upInstance.get();
}