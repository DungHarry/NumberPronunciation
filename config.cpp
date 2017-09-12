/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the Config class in C++ programming language
*/

#include "config.h"

Config::Config() :
	m_upLang(new Language()),
    m_upAttributes(new vector<Container>()),
	m_upSpecialDigitAttributes(new set<Container>()),
	m_upMultipleDigitsAttributes(new set<Container>()),
	m_upNormalDigitAttributes(new set<Container>()),
	m_upConditionAppendAttributes(new set<Container>()),
	m_upConditionDigitAttributes(new set<Container>())
{

}

Config::Config(const char *cpcLangName, const char *cpcLocaleName) :
	m_upLang(new Language(cpcLangName, cpcLocaleName)),
    m_upAttributes(new vector<Container>()),
	m_upSpecialDigitAttributes(new set<Container>()),
	m_upMultipleDigitsAttributes(new set<Container>()),
	m_upNormalDigitAttributes(new set<Container>()),
	m_upConditionAppendAttributes(new set<Container>()),
	m_upConditionDigitAttributes(new set<Container>())
{

}

Config::Config(const Config &conf) : 
	m_upLang((conf.m_upLang.get() == nullptr || conf.m_upLang->getName() == nullptr) ? nullptr : new Language(conf.m_upLang->getName(), conf.m_upLang->getLocaleName())),
    m_upAttributes(new vector<Container>()),
	m_upSpecialDigitAttributes(new set<Container>()),
	m_upMultipleDigitsAttributes(new set<Container>()),
	m_upNormalDigitAttributes(new set<Container>()),
	m_upConditionAppendAttributes(new set<Container>()),
	m_upConditionDigitAttributes(new set<Container>())
{
	if (conf.m_upAttributes.get() != nullptr) {
        for (vector<Container>::iterator iter = conf.m_upAttributes->begin(); iter != conf.m_upAttributes->end(); ++iter)
			this->m_upAttributes->push_back(*iter);
	}

	if (conf.m_upSpecialDigitAttributes.get() != nullptr) {
		for (set<Container>::iterator iter = conf.m_upSpecialDigitAttributes->begin(); iter != conf.m_upSpecialDigitAttributes->end(); ++iter)
			this->m_upSpecialDigitAttributes->insert(*iter);
	}

	if (conf.m_upNormalDigitAttributes.get() != nullptr) {
		for (set<Container>::iterator iter = conf.m_upNormalDigitAttributes->begin(); iter != conf.m_upSpecialDigitAttributes->end(); ++iter)
			this->m_upNormalDigitAttributes->insert(*iter);
	}

	if (conf.m_upMultipleDigitsAttributes.get() != nullptr) {
		for (set<Container>::iterator iter = conf.m_upMultipleDigitsAttributes->begin(); iter != conf.m_upMultipleDigitsAttributes->end(); ++iter)
			this->m_upMultipleDigitsAttributes->insert(*iter);
	}
}

Config::~Config() {
	this->m_upLang.reset();

	if (this->m_upSpecialDigitAttributes.get() != nullptr) {
		this->m_upSpecialDigitAttributes->clear();
		this->m_upSpecialDigitAttributes.reset();
	}

	if (this->m_upNormalDigitAttributes.get() != nullptr) {
		this->m_upNormalDigitAttributes->clear();
		this->m_upNormalDigitAttributes.reset();
	}

	if (this->m_upConditionAppendAttributes.get() != nullptr) {
		this->m_upConditionAppendAttributes->clear();
		this->m_upConditionAppendAttributes.reset();
	}

	if (this->m_upConditionDigitAttributes.get() != nullptr) {
		this->m_upConditionDigitAttributes->clear();
		this->m_upConditionDigitAttributes.reset();
	}

	if (this->m_upMultipleDigitsAttributes.get() != nullptr) {
		this->m_upMultipleDigitsAttributes->clear();
		this->m_upMultipleDigitsAttributes.reset();
	}

	if (this->m_upAttributes.get() != nullptr) {
		this->m_upAttributes->clear();
		this->m_upAttributes.reset();
	}
}

Language* Config::getLang() {
	return this->m_upLang.get();
}

void Config::setLang(Language *pLang) {
	this->m_upLang.reset(pLang);
}

vector<Container> *Config::getAttributes() {
	return this->m_upAttributes.get();
}

set<Container>* Config::getSpecialDigitAttributes() {
	return this->m_upSpecialDigitAttributes.get();
}

set<Container>* Config::getNormalDigitAttributes() {
	return this->m_upNormalDigitAttributes.get();
}

set<Container>* Config::getConditionAppendAttributes() {
	return this->m_upConditionAppendAttributes.get();
}

set<Container>* Config::getConditionDigitAttributes() {
	return this->m_upConditionDigitAttributes.get();
}

set<Container>* Config::getMultipleDigitsAttributes() {
	return this->m_upMultipleDigitsAttributes.get();
}

bool Config::classify() {
    int32_t i;
    Attribute *pAttribute;

	if (this->m_upAttributes.get() == nullptr || this->m_upAttributes->size() <= 0 || this->m_upConditionAppendAttributes.get() == nullptr || this->m_upConditionDigitAttributes.get() == nullptr || this->m_upNormalDigitAttributes.get() == nullptr || this->m_upSpecialDigitAttributes.get() == nullptr)
		return false;

	this->m_upConditionAppendAttributes->clear();
	this->m_upConditionDigitAttributes->clear();
	this->m_upNormalDigitAttributes->clear();
	this->m_upSpecialDigitAttributes->clear();

    for (i = 0; i < this->m_upAttributes->size(); ++ i) {
        if((pAttribute = dynamic_cast<Attribute *>(this->m_upAttributes->at(i).getData().get())) == nullptr)
            continue;

        if (pAttribute->getId() == ATTRIBUTE_TYPE_CONDITION_APPEND)
            this->m_upConditionAppendAttributes->insert(this->m_upAttributes->at(i));
        else if (pAttribute->getId() == ATTRIBUTE_TYPE_CONDITION_DIGIT)
            this->m_upConditionDigitAttributes->insert(this->m_upAttributes->at(i));
        else if (pAttribute->getId() == ATTRIBUTE_TYPE_MULTIPLE_DIGITS)
            this->m_upMultipleDigitsAttributes->insert(this->m_upAttributes->at(i));
        else if (pAttribute->getId() == ATTRIBUTE_TYPE_NORMAL_DIGIT)
            this->m_upNormalDigitAttributes->insert(this->m_upAttributes->at(i));
        else if (pAttribute->getId() == ATTRIBUTE_TYPE_SPECIAL_DIGIT)
            this->m_upSpecialDigitAttributes->insert(this->m_upAttributes->at(i));
	}

	return true;
}

bool Config::less(const Comparable &config) {
	const Config *pConfig = dynamic_cast<const Config *>(&config);

	return (pConfig == nullptr || pConfig->m_upLang.get() == nullptr || this->m_upLang.get() == nullptr) ? false : this->m_upLang->less(*(pConfig->m_upLang));
}

bool Config::equal(const Comparable &config) {
	const Config *pConfig = dynamic_cast<const Config *>(&config);

	return (pConfig == nullptr || pConfig->m_upLang.get() == nullptr || this->m_upLang.get() == nullptr) ? false : this->m_upLang->equal(*(pConfig->m_upLang));
}
