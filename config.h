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

    Author:Dung Harry
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Config class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_CONFIG_H_
#define _COC_COC_NUMBER_PRONUNCIATION_CONFIG_H_

#include <set>
#include <vector>
#include <utility>
#include "container.h"
#include "language.h"
#include "condition_append_attribute.h"

class Config : public Base, public Comparable {
public:
	Config();
	Config(const char *cpcLangName, const char *cpcLocaleName);
	Config(const Config &conf);
	virtual ~Config();

	Language* getLang();
	void setLang(Language *pLang);

    vector<Container>* getAttributes();

	set<Container>* getSpecialDigitAttributes();

	set<Container>* getNormalDigitAttributes();

	set<Container>* getConditionAppendAttributes();

	set<Container>* getConditionDigitAttributes();

	set<Container>* getMultipleDigitsAttributes();

    set<Container>* getConditionAppendDigitsEndAttributes();

    int16_t getMaxUnits();

	bool classify();

	virtual bool less(const Comparable &config);
	virtual bool equal(const Comparable &config);
private:
	unique_ptr<Language> m_upLang;

    unique_ptr<vector<Container>> m_upAttributes;
	unique_ptr<set<Container>> m_upSpecialDigitAttributes;
	unique_ptr<set<Container>> m_upNormalDigitAttributes;
	unique_ptr<set<Container>> m_upMultipleDigitsAttributes;
	unique_ptr<set<Container>> m_upConditionAppendAttributes;
    unique_ptr<set<Container>> m_upConditionAppendDigitsEndAttributes;
	unique_ptr<set<Container>> m_upConditionDigitAttributes;

    int16_t m_iMaxUnits;
};

#endif
