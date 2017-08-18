/*
	Author: Dung Ly Viet
	Date created: August 18th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the Language class in C++ programming language
*/

#include "language.h"

Language::Language() :
	m_apsName(NULL)
{

}

Language::Language(const char *cpcName) :
	m_apsName(cpcName == NULL ? NULL : new string(cpcName))
{

}

Language::~Language() {
	this->m_apsName.reset();
}

const char* Language::getName() {
	return (this->m_apsName.get() == NULL) ? NULL : this->m_apsName->c_str();
}

void Language::setName(const char *cpcName) {
	this->m_apsName.reset(cpcName == NULL ? NULL : new string(cpcName));
}

bool Language::less(const Comparable &lang) {
	const Language *pLang = dynamic_cast<const Language *>(&lang);

	return (this->m_apsName.get() == NULL || this->m_apsName->c_str() == NULL || pLang == NULL || pLang->m_apsName.get() == NULL || pLang->m_apsName->c_str() == NULL) ? false : (strcmp(this->m_apsName->c_str(), pLang->m_apsName->c_str()) < 0);
}

bool Language::equal(const Comparable &lang) {
	const Language *pLang = dynamic_cast<const Language *>(&lang);

	return (this->m_apsName.get() == NULL || this->m_apsName->c_str() == NULL || pLang == NULL || pLang->m_apsName.get() == NULL || pLang->m_apsName->c_str() == NULL) ? false : (strcmp(this->m_apsName->c_str(), pLang->m_apsName->c_str()) == 0);
}