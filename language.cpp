/*
	Author: Dung Ly Viet
	Date created: August 18th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the Language class in C++ programming language
*/

#include "language.h"

Language::Language() :
    m_apsName(NULL),
    m_apsLocaleName (new string(LANGUAGE_LOCALE_NAME_DEFAULT_VALUE))
{

}

Language::Language(const char *cpcName, const char *cpcLocaleName) :
	m_apsName(cpcName == NULL ? NULL : new string(cpcName))
{

}

Language::~Language() {
	this->m_apsName.reset();
    this->m_apsLocaleName.reset();
}

const char* Language::getName() {
	return (this->m_apsName.get() == NULL) ? NULL : this->m_apsName->c_str();
}

void Language::setName(const char *cpcName) {
	this->m_apsName.reset(cpcName == NULL ? NULL : new string(cpcName));
}

const char* Language::getLocaleName() {
    return (this->m_apsLocaleName.get() == NULL) ? NULL : this->m_apsLocaleName->c_str();
}

void Language::setLocaleName(const char *cpcLocaleName) {
    this->m_apsLocaleName.reset(cpcLocaleName == NULL ? NULL : new string(cpcLocaleName));
}

bool Language::less(const Comparable &lang) {
	const Language *pLang = dynamic_cast<const Language *>(&lang);

	return (this->m_apsName.get() == NULL || this->m_apsName->c_str() == NULL || pLang == NULL || pLang->m_apsName.get() == NULL || pLang->m_apsName->c_str() == NULL) ? false : (strcmp(this->m_apsName->c_str(), pLang->m_apsName->c_str()) < 0);
}

bool Language::equal(const Comparable &lang) {
	const Language *pLang = dynamic_cast<const Language *>(&lang);

	return (this->m_apsName.get() == NULL || this->m_apsName->c_str() == NULL || pLang == NULL || pLang->m_apsName.get() == NULL || pLang->m_apsName->c_str() == NULL) ? false : (strcmp(this->m_apsName->c_str(), pLang->m_apsName->c_str()) == 0);
}
