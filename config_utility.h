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

	Description: this is the header file of the ConfigUtility class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_CONFIG_UTILITY_H_
#define _COC_COC_NUMBER_PRONUNCIATION_CONFIG_UTILITY_H_

#include <memory>
#include "condition_append_attribute.h"
#include "utility.h"
#include "config.h"

class ConfigUtility : public Utility {
public:
	ConfigUtility();
	virtual ~ConfigUtility();

	int16_t getMaxConditionAppendAttributeUnits(const set<Container> *pAppendAttributes);

	static ConfigUtility* getInstance();
private:
	static unique_ptr<ConfigUtility> m_upInstance;
};

#endif
