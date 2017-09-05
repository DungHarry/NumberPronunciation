/*
	Author: Dung Ly Viet
	Date created: September 5th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the PSParseConfigs class in C++ programming language
*/

#include "ps_parse_configs.h"

PSParseConfigs::PSParseConfigs() :
	PipelineState()
{
	this->m_eStateType = PIPELINE_STATE_TYPE_PARSE_CONFIGS;

	this->constructPossibleStates();
}

PSParseConfigs::PSParseConfigs(Pipeline *pPipeline, map<Key, shared_ptr<Base>> *pData) :
	PipelineState(pPipeline, pData, PIPELINE_STATE_TYPE_PARSE_CONFIGS)
{
	this->constructPossibleStates();
}

PSParseConfigs::~PSParseConfigs() {

}

bool PSParseConfigs::execute() {
	Key k;
	ConfigName<wchar_t> *pwcConfigName;
	Config *pConfig;

	if (this->m_spData.get() == nullptr || StringUtility::getInstance() == nullptr || FileHandler::getInstance() == nullptr || ParseHandler::getInstance() == nullptr) {
		this->m_eNextState = PIPELINE_STATE_FINISH;

		return false;
	}

	for (k = 1; k < LANGUAGE_MAX_VALUE && this->isConfigNameAvailable(k) == true; k ++)
		if ((pwcConfigName = dynamic_cast<ConfigName<wchar_t> *>(this->m_spData->at(k).get())) != nullptr) {
			if (this->readConfigFile(pwcConfigName) == false)
				continue;

			if ((pConfig = this->parseConfigFile()) == nullptr)
				continue;

			if (this->addConfig(this->m_spPipeline->getManager(), &pConfig) == false) {
				delete pConfig;
				
				continue;
			}
		}
	
	if (this->m_spPipeline->getManager() == nullptr || this->m_spPipeline->getManager()->getObjects() == nullptr || this->m_spPipeline->getManager()->getObjects()->size() <= 0) {
		this->m_eNextState = PIPELINE_STATE_FINISH;

		return false;
	}

	this->m_eNextState = PIPELINE_STATE_TYPE_CHOOSE_LANG; 

	return true;
}

PipelineStateType PSParseConfigs::determineNextStateType() const {
	return this->m_eNextState;
}

bool PSParseConfigs::cleanup() {
	Manager *pManager;

	if (this->m_spPipeline.get() == nullptr || (pManager = this->m_spPipeline->getManager()) == nullptr)
		return false;

	pManager->cleanUp();

	return true;
}

bool PSParseConfigs::constructPossibleStates() {
	if (this->m_upPossibleStates.get() == nullptr)
		return false;

	this->m_upPossibleStates->insert(PIPELINE_STATE_FINISH);
	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_CHOOSE_LANG);

	return true;
}

bool PSParseConfigs::isConfigNameAvailable(const Key k) {
	map<Key, shared_ptr<Base>>::iterator iter;
	
	if (this->m_spData.get() == nullptr || this->m_spData->size() <= 0)
		return false;

	return (iter = this->m_spData->find(k)) != this->m_spData->end() ? true : false;
}

bool PSParseConfigs::readConfigFile(ConfigName<wchar_t> *pwcConfigName) {
	char *pcConfigName;
	bool bResult;

	if (StringUtility::getInstance() == nullptr || FileHandler::getInstance() == nullptr || pwcConfigName == nullptr || pwcConfigName->getValue() == nullptr)
		return false;

	if ((pcConfigName = StringUtility::getInstance()->convertToChar(pwcConfigName->getValue())) == nullptr)
		return false;

	FileHandler::getInstance()->setFileName(pcConfigName);
	FileHandler::getInstance()->setType(FILE_HANDLER_TYPE_READ);

	bResult = FileHandler::getInstance()->execute();

	delete[] pcConfigName;

	return bResult;
}

Config* PSParseConfigs::parseConfigFile() {
	if (ParseHandler::getInstance() == nullptr || FileHandler::getInstance() == nullptr || FileHandler::getInstance()->getBufferContent() == nullptr)
		return nullptr;

	ParseHandler::getInstance()->setBuffer(FileHandler::getInstance()->getBufferContent());

	if (ParseHandler::getInstance()->execute() == false)
		return nullptr;

	return ParseHandler::getInstance()->releaseConfig();
}

bool PSParseConfigs::addConfig(Manager *pManager, Config **pConfig) {
	if (pManager == nullptr || pManager->getObjects() == nullptr || pConfig == nullptr || *pConfig == nullptr)
		return false;

	pManager->getObjects()->insert(Container(shared_ptr<Comparable>(*pConfig)));

	return true;
}