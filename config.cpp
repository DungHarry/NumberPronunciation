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
    m_upConditionAppendDigitsEndAttributes(new set<Container>()),
    m_upConditionDigitAttributes(new set<Container>()),
    m_iMaxUnits (0)
{

}

Config::Config(const char *cpcLangName, const char *cpcLocaleName) :
	m_upLang(new Language(cpcLangName, cpcLocaleName)),
    m_upAttributes(new vector<Container>()),
	m_upSpecialDigitAttributes(new set<Container>()),
	m_upMultipleDigitsAttributes(new set<Container>()),
	m_upNormalDigitAttributes(new set<Container>()),
	m_upConditionAppendAttributes(new set<Container>()),
    m_upConditionAppendDigitsEndAttributes(new set<Container>()),
    m_upConditionDigitAttributes(new set<Container>()),
    m_iMaxUnits (0)
{

}

Config::Config(const Config &conf) : 
	m_upLang((conf.m_upLang.get() == nullptr || conf.m_upLang->getName() == nullptr) ? nullptr : new Language(conf.m_upLang->getName(), conf.m_upLang->getLocaleName())),
    m_upAttributes(new vector<Container>()),
	m_upSpecialDigitAttributes(new set<Container>()),
	m_upMultipleDigitsAttributes(new set<Container>()),
	m_upNormalDigitAttributes(new set<Container>()),
	m_upConditionAppendAttributes(new set<Container>()),
    m_upConditionAppendDigitsEndAttributes(new set<Container>()),
    m_upConditionDigitAttributes(new set<Container>()),
    m_iMaxUnits (conf.m_iMaxUnits)
{
    vector<Container>::iterator vecIter;
    set<Container>::iterator setIter;

	if (conf.m_upAttributes.get() != nullptr) {
        for (vecIter = conf.m_upAttributes->begin(); vecIter != conf.m_upAttributes->end(); ++ vecIter)
            this->m_upAttributes->push_back(*vecIter);
	}

	if (conf.m_upSpecialDigitAttributes.get() != nullptr) {
        for (setIter = conf.m_upSpecialDigitAttributes->begin(); setIter != conf.m_upSpecialDigitAttributes->end(); ++ setIter)
            this->m_upSpecialDigitAttributes->insert(*setIter);
	}

	if (conf.m_upNormalDigitAttributes.get() != nullptr) {
        for (setIter = conf.m_upNormalDigitAttributes->begin(); setIter != conf.m_upSpecialDigitAttributes->end(); ++ setIter)
            this->m_upNormalDigitAttributes->insert(*setIter);
	}

	if (conf.m_upMultipleDigitsAttributes.get() != nullptr) {
        for (setIter = conf.m_upMultipleDigitsAttributes->begin(); setIter != conf.m_upMultipleDigitsAttributes->end(); ++ setIter)
            this->m_upMultipleDigitsAttributes->insert(*setIter);
	}

    if(conf.m_upConditionAppendAttributes.get() != nullptr) {
        for(setIter = conf.m_upConditionAppendAttributes->begin(); setIter != conf.m_upConditionAppendAttributes->end(); ++ setIter)
            this->m_upConditionAppendAttributes->insert(*setIter);
    }

    if(conf.m_upConditionAppendDigitsEndAttributes.get() != nullptr) {
        for(setIter = conf.m_upConditionAppendDigitsEndAttributes->begin(); setIter != conf.m_upConditionAppendDigitsEndAttributes->end(); ++ setIter)
            this->m_upConditionAppendDigitsEndAttributes->insert(*setIter);
    }

    if(conf.m_upConditionDigitAttributes.get() != nullptr) {
        for(setIter = conf.m_upConditionDigitAttributes->begin(); setIter != conf.m_upConditionDigitAttributes->end(); ++ setIter)
            this->m_upConditionDigitAttributes->insert(*setIter);
    }
}

Config::~Config() {
	this->m_upLang.reset();

    if(this->m_upConditionAppendDigitsEndAttributes.get() != nullptr) {
        this->m_upConditionAppendDigitsEndAttributes->clear();
        this->m_upConditionAppendDigitsEndAttributes.reset();
    }

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

set<Container>* Config::getConditionAppendDigitsEndAttributes() {
    return this->m_upConditionAppendDigitsEndAttributes.get();
}

int16_t Config::getMaxUnits() {
    return this->m_iMaxUnits;
}

bool Config::classify() {
    int32_t i;
    Attribute *pAttribute;
    ConditionAppendAttribute *pConditionAppendAttribute;
    set<Container>::iterator iter;

	if (this->m_upAttributes.get() == nullptr || this->m_upAttributes->size() <= 0 || this->m_upConditionAppendAttributes.get() == nullptr || this->m_upConditionDigitAttributes.get() == nullptr || this->m_upNormalDigitAttributes.get() == nullptr || this->m_upSpecialDigitAttributes.get() == nullptr)
		return false;

	this->m_upConditionAppendAttributes->clear();
	this->m_upConditionDigitAttributes->clear();
	this->m_upNormalDigitAttributes->clear();
	this->m_upSpecialDigitAttributes->clear();

    for (i = 0; i < this->m_upAttributes->size(); ++ i) {
        if((pAttribute = dynamic_cast<Attribute *>(this->m_upAttributes->at(i).getData().get())) == nullptr)
            continue;

        if (pAttribute->getType() == ATTRIBUTE_TYPE_CONDITION_APPEND)
            this->m_upConditionAppendAttributes->insert(this->m_upAttributes->at(i));
        else if (pAttribute->getType() == ATTRIBUTE_TYPE_CONDITION_DIGIT)
            this->m_upConditionDigitAttributes->insert(this->m_upAttributes->at(i));
        else if(pAttribute->getType() == ATTRIBUTE_TYPE_CONDITION_APPEND_DIGITS_END)
            this->m_upConditionAppendDigitsEndAttributes->insert(this->m_upAttributes->at(i));
        else if (pAttribute->getType() == ATTRIBUTE_TYPE_MULTIPLE_DIGITS)
            this->m_upMultipleDigitsAttributes->insert(this->m_upAttributes->at(i));
        else if (pAttribute->getType() == ATTRIBUTE_TYPE_NORMAL_DIGIT)
            this->m_upNormalDigitAttributes->insert(this->m_upAttributes->at(i));
        else if (pAttribute->getType() == ATTRIBUTE_TYPE_SPECIAL_DIGIT)
            this->m_upSpecialDigitAttributes->insert(this->m_upAttributes->at(i));
	}

    for(this->m_iMaxUnits = 0, iter = this->m_upConditionAppendAttributes->begin(); iter != this->m_upConditionAppendAttributes->end(); ++ iter)
        if((pConditionAppendAttribute = dynamic_cast<ConditionAppendAttribute *>(iter->getData().get())) != nullptr && this->m_iMaxUnits < pConditionAppendAttribute->getUnits())
            this->m_iMaxUnits = pConditionAppendAttribute->getUnits();

	return true;
}

bool Config::less(const Comparable &config) {
	const Config *pConfig = dynamic_cast<const Config *>(&config);

    return (pConfig == nullptr || pConfig->m_upLang.get() == nullptr || this->m_upLang.get() == nullptr) ? true : this->m_upLang->less(*(pConfig->m_upLang));
}

bool Config::equal(const Comparable &config) {
	const Config *pConfig = dynamic_cast<const Config *>(&config);

	return (pConfig == nullptr || pConfig->m_upLang.get() == nullptr || this->m_upLang.get() == nullptr) ? false : this->m_upLang->equal(*(pConfig->m_upLang));
}
