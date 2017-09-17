/*
	Author: Dung Ly Viet
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
