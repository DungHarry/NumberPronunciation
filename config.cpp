/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the Config class in C++ programming language
*/

#include "config.h"

Config::Config() :
	m_apLang(new Language()),
	m_apAttributes(new vector<shared_ptr<Attribute>>()),
	m_apSpecialDigitAttributes(new set<Container>()),
	m_apNormalDigitAttributes(new set<Container>()),
	m_apConditionAppendAttributes(new set<Container>()),
	m_apConditionDigitAttributes(new set<Container>())
{

}

Config::Config(const char *cpcLangName) :
	m_apLang(new Language(cpcLangName)),
	m_apAttributes(new vector<shared_ptr<Attribute>>()),
	m_apSpecialDigitAttributes(new set<Container>()),
	m_apNormalDigitAttributes(new set<Container>()),
	m_apConditionAppendAttributes(new set<Container>()),
	m_apConditionDigitAttributes(new set<Container>())
{

}

Config::Config(const Config &conf) : 
	m_apLang((conf.m_apLang.get() == NULL || conf.m_apLang->getName() == NULL) ? NULL : new Language(conf.m_apLang->getName())),
	m_apAttributes(new vector<shared_ptr<Attribute>>()),
	m_apSpecialDigitAttributes(new set<Container>()),
	m_apNormalDigitAttributes(new set<Container>()),
	m_apConditionAppendAttributes(new set<Container>()),
	m_apConditionDigitAttributes(new set<Container>())
{
	if (conf.m_apAttributes.get() != NULL) {
		for (vector<shared_ptr<Attribute>>::iterator iter = conf.m_apAttributes->begin(); iter != conf.m_apAttributes->end(); ++iter)
			this->m_apAttributes->push_back(*iter);
	}

	if (conf.m_apSpecialDigitAttributes.get() != NULL) {
		for (set<Container>::iterator iter = conf.m_apSpecialDigitAttributes->begin(); iter != conf.m_apSpecialDigitAttributes->end(); ++iter)
			this->m_apSpecialDigitAttributes->insert(*iter);
	}

	if (conf.m_apNormalDigitAttributes.get() != NULL) {
		for (set<Container>)
	}
}

Config::~Config() {
	this->m_apLang.reset();

	if (this->m_apSpecialDigitAttributes.get() != NULL) {
		this->m_apSpecialDigitAttributes->clear();
		this->m_apSpecialDigitAttributes.reset();
	}

	if (this->m_apNormalDigitAttributes.get() != NULL) {
		this->m_apNormalDigitAttributes->clear();
		this->m_apNormalDigitAttributes.reset();
	}

	if (this->m_apConditionAppendAttributes.get() != NULL) {
		this->m_apConditionAppendAttributes->clear();
		this->m_apConditionAppendAttributes.reset();
	}

	if (this->m_apConditionDigitAttributes.get() != NULL) {
		this->m_apConditionDigitAttributes->clear();
		this->m_apConditionDigitAttributes.reset();
	}

	if (this->m_apAttributes.get() != NULL) {
		this->m_apAttributes->clear();
		this->m_apAttributes.reset();
	}
}

Language* Config::getLang() {
	return this->m_apLang.get();
}

void Config::setLang(Language *pLang) {
	this->m_apLang.reset(pLang);
}

vector<shared_ptr<Attribute>>* Config::getAttributes() {
	return this->m_apAttributes.get();
}

set<Container>* Config::getSpecialDigitAttributes() {
	return this->m_apSpecialDigitAttributes.get();
}

set<Container>* Config::getNormalDigitAttributes() {
	return this->m_apNormalDigitAttributes.get();
}

set<Container>* Config::getConditionAppendAttributes() {
	return this->m_apConditionAppendAttributes.get();
}

set<Container>* Config::getConditionDigitAttributes() {
	return this->m_apConditionDigitAttributes.get();
}

bool Config::classify() {

}

bool Config::less(const Comparable &config) {
	const Config *pConfig = dynamic_cast<const Config *>(&config);

	return (pConfig == NULL || pConfig->m_apLang.get() == NULL || this->m_apLang.get() == NULL) ? false : this->m_apLang->less(*(pConfig->m_apLang));
}

bool Config::equal(const Comparable &config) {
	const Config *pConfig = dynamic_cast<const Config *>(&config);

	return (pConfig == NULL || pConfig->m_apLang.get() == NULL || this->m_apLang.get() == NULL) ? false : this->m_apLang->equal(*(pConfig->m_apLang));
}