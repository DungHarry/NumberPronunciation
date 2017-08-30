/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Config class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_CONFIG_H_
#define _COC_COC_NUMBER_PRONUNCIATION_CONFIG_H_

#include "container.h"
#include "attribute.h"
#include "language.h"
#include <set>
#include <vector>
#include <utility>

class Config : public Base, public Comparable {
public:
	Config();
	Config(const char *cpcLangName, const char *cpcLocaleName);
	Config(const Config &conf);
	virtual ~Config();

	Language* getLang();
	void setLang(Language *pLang);

	vector<shared_ptr<Attribute>>* getAttributes();

	set<Container>* getSpecialDigitAttributes();

	set<Container>* getNormalDigitAttributes();

	set<Container>* getConditionAppendAttributes();

	set<Container>* getConditionDigitAttributes();

	set<Container>* getMultipleDigitsAttributes();

	bool classify();

	virtual bool less(const Comparable &config);
	virtual bool equal(const Comparable &config);
private:
	unique_ptr<Language> m_upLang;

	unique_ptr<vector<shared_ptr<Attribute>>> m_upAttributes;
	unique_ptr<set<Container>> m_upSpecialDigitAttributes;
	unique_ptr<set<Container>> m_upNormalDigitAttributes;
	unique_ptr<set<Container>> m_upMultipleDigitsAttributes;
	unique_ptr<set<Container>> m_upConditionAppendAttributes;
	unique_ptr<set<Container>> m_upConditionDigitAttributes;
};

#endif