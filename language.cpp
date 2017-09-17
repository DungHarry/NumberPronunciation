/*
	Author: Dung Ly Viet
	Date created: August 18th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the Language class in C++ programming language
*/

#include <iostream>
#include "language.h"

Language::Language() :
    m_upsName(nullptr),
    m_upsLocaleName (new string(LANGUAGE_LOCALE_NAME_DEFAULT_VALUE))
{

}

Language::Language(const char *cpcName, const char *cpcLocaleName) :
	m_upsName(cpcName == nullptr ? nullptr : new string(cpcName))
{

}

Language::~Language() {
	this->m_upsName.reset();
    this->m_upsLocaleName.reset();
}

const char* Language::getName() {
	return (this->m_upsName.get() == nullptr) ? nullptr : this->m_upsName->c_str();
}

void Language::setName(const char *cpcName) {
	this->m_upsName.reset(cpcName == nullptr ? nullptr : new string(cpcName));
}

const char* Language::getLocaleName() {
    return (this->m_upsLocaleName.get() == nullptr) ? nullptr : this->m_upsLocaleName->c_str();
}

void Language::setLocaleName(const char *cpcLocaleName) {
    this->m_upsLocaleName.reset(cpcLocaleName == nullptr ? nullptr : new string(cpcLocaleName));
}

bool Language::less(const Comparable &lang) {
	const Language *pLang = dynamic_cast<const Language *>(&lang);

	return (this->m_upsName.get() == nullptr || this->m_upsName->c_str() == nullptr || pLang == nullptr || pLang->m_upsName.get() == nullptr || pLang->m_upsName->c_str() == nullptr) ? false : (strcmp(this->m_upsName->c_str(), pLang->m_upsName->c_str()) < 0);
}

bool Language::equal(const Comparable &lang) {
	const Language *pLang = dynamic_cast<const Language *>(&lang);

	return (this->m_upsName.get() == nullptr || this->m_upsName->c_str() == nullptr || pLang == nullptr || pLang->m_upsName.get() == nullptr || pLang->m_upsName->c_str() == nullptr) ? false : (strcmp(this->m_upsName->c_str(), pLang->m_upsName->c_str()) == 0);
}
