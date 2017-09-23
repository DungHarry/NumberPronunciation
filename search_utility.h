/*
    Author: Dung Harry
	Date created: August 30th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the SearchUtility class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_SEARCH_UTILITY_H_
#define _COC_COC_NUMBER_PRONUNCIATION_SEARCH_UTILITY_H_

#include <set>
#include <memory>
#include "utility.h"
#include "container.h"
#include "condition_append_attribute.h"
#include "condition_digit_attribute.h"
#include "multiple_digits_attribute.h"
#include "digit_attribute.h"
#include "condition_append_digits_end_attribute.h"

class SearchUtility : public Utility {
public:
	SearchUtility();
	virtual ~SearchUtility();

    Comparable* find(const set<Container> *pSet, const Container &con);
    Comparable* find(const set<Container> *pSet, int16_t iPosition);
    Comparable* find(const set<Container> *pSet, char cDigit);
    Comparable* find(const set<Container> *pSet, const wchar_t *cpwcMultipleDigits);
    Comparable* find(const set<Container> *pSet, char cDigit, int16_t iPosition);
    Comparable* find(const set<Container> *pSet, int16_t iPosition, const wchar_t *cpwcEndDigits);

	static SearchUtility* getInstance();
private:
	static unique_ptr<SearchUtility> m_upInstance;
};

#endif
