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
	Date created: August 30th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the ConfigUtility class in C++ programming language
*/

#include "config_utility.h"

unique_ptr<ConfigUtility> ConfigUtility::m_upInstance (nullptr);

ConfigUtility::ConfigUtility() :
	Utility(UTILITY_TYPE_CONFIG)
{

}

ConfigUtility::~ConfigUtility() {

}

int16_t ConfigUtility::getMaxConditionAppendAttributeUnits(const set<Container> *pAppendAttributes) {
	const ConditionAppendAttribute *pConditionAppendAttribute = nullptr;
	
	if (pAppendAttributes == nullptr || pAppendAttributes->size() <= 0 || (pConditionAppendAttribute = dynamic_cast<const ConditionAppendAttribute *>(&(*(pAppendAttributes->rbegin())))) == nullptr)
		return 0;

	return pConditionAppendAttribute->getUnits();
}

ConfigUtility* ConfigUtility::getInstance() {
	if (m_upInstance.get() == nullptr)
		m_upInstance.reset(new ConfigUtility());

	return m_upInstance.get();
}
