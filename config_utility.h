/*
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
