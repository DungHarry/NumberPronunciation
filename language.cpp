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
