/*
	Author: Dung Ly Viet
	Date created: September 5th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the PSChooseLang class in C++ programming language
*/

#include "ps_choose_lang.h"

#define PS_CHOOSE_LANG_BUFFER_SIZE (static_cast<int32_t>(1 << 10))

PSChooseLanguage::PSChooseLanguage() :
	PipelineState(),
	m_iMaxTries (PS_CHOOSE_LANGUAGE_MAX_TRIES_DEFAULT_VALUE),
	m_iTryCount (0)
{
	this->m_eStateType = PIPELINE_STATE_TYPE_CHOOSE_LANG;

	this->constructPossibleStates();
	this->determineLangKey();

	if (this->m_spData.get() != nullptr)
		(*(this->m_spData.get()))[this->m_kLangKey] = shared_ptr<Base>(new StringData());
}

PSChooseLanguage::PSChooseLanguage(shared_ptr<Pipeline> pipeline, shared_ptr<map<Key, shared_ptr<Base>>> data, const int16_t iMaxTries) :
	PipelineState(pipeline, data, PIPELINE_STATE_TYPE_CHOOSE_LANG),
	m_iMaxTries (iMaxTries <= 0 ? PS_CHOOSE_LANGUAGE_MAX_TRIES_DEFAULT_VALUE : iMaxTries),
	m_iTryCount (0)
{
	this->constructPossibleStates();
	this->determineLangKey();

	if (this->m_spData.get() != nullptr)
		(*(this->m_spData.get()))[this->m_kLangKey] = shared_ptr<Base>(new StringData());
}

PSChooseLanguage::~PSChooseLanguage() {
	this->cleanup();
}

bool PSChooseLanguage::execute() {
	char *pcBuffer;
	Config *pConfig;
	
	if (StandardIOUtility::getInstance() == nullptr || this->m_iTryCount >= this->m_iMaxTries) {
		this->m_eNextState = PIPELINE_STATE_TYPE_FINISH;

		return false;
	}

	pcBuffer = new char[PS_CHOOSE_LANG_BUFFER_SIZE];

	if (StandardIOUtility::getInstance()->readLine(pcBuffer, PS_CHOOSE_LANG_BUFFER_SIZE) == false) {
		this->m_eNextState = PIPELINE_STATE_TYPE_FINISH;
		
		delete[] pcBuffer;
		
		return false;
	}

	if ((pConfig = this->isLangAvailable(pcBuffer)) == nullptr) {
		this->m_iTryCount ++;

		this->m_eNextState = PIPELINE_STATE_TYPE_HELP;

		delete[] pcBuffer;

		return false;
	}

	this->m_spData->at(m_kLangKey).reset(new StringData(pcBuffer));

	if (pConfig->getLang() != nullptr && pConfig->getLang()->getLocaleName() != nullptr) {
		LocaleHandler::getInstance()->setLocaleName(pConfig->getLang()->getLocaleName());
		LocaleHandler::getInstance()->setScope(LOCALE_HANDLER_SCOPE_ALL);

		LocaleHandler::getInstance()->execute();
	}

	this->m_eNextState = PIPELINE_STATE_TYPE_INPUT_NUMBER_STRING;
	this->m_iTryCount = 0;

	delete[] pcBuffer;

	return true;
}

PipelineStateType PSChooseLanguage::determineNextStateType() const {
	PSHelp *pHelpPipeline;

	if (this->m_eNextState == PIPELINE_STATE_TYPE_HELP && this->m_spPipeline.get() != nullptr && (pHelpPipeline = dynamic_cast<PSHelp *>(this->m_spPipeline->getStateByKey(PIPELINE_STATE_TYPE_HELP))) != nullptr)
		pHelpPipeline->setHelpType(PS_HELP_TYPE_LANG);

	return this->m_eNextState;
}

bool PSChooseLanguage::cleanup() {
	if (this->m_spData.get() == nullptr)
		return false;

	if (this->m_spData->find(this->m_kLangKey) != this->m_spData->end() && this->m_spData->at(this->m_kLangKey).get() != nullptr)
		this->m_spData->at(this->m_kLangKey).reset();

	this->m_iTryCount = 0;

	return true;
}

Key PSChooseLanguage::getLangKey() {
	return this->m_kLangKey;
}

int16_t PSChooseLanguage::getMaxTries() {
	return this->m_iMaxTries;
}

void PSChooseLanguage::setMaxTries(const int16_t iMaxTries) {
	if (iMaxTries <= 0)
		return;

	this->m_iMaxTries = iMaxTries;
}

int16_t PSChooseLanguage::getTryCount() {
	return this->m_iTryCount;
}

void PSChooseLanguage::setTryCount(const int16_t iTryCount) {
	if (iTryCount <= 0)
		return;

	this->m_iTryCount = iTryCount;
}

bool PSChooseLanguage::constructPossibleStates() {
	if (this->m_upPossibleStates.get() == nullptr)
		return false;

	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_FINISH);
	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_HELP);
	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_INPUT_NUMBER_STRING);

	return true;
}

bool PSChooseLanguage::determineLangKey() {
	Key k;
	map<Key, shared_ptr<Base>>::iterator iter;

	if (this->m_spData.get() == nullptr)
		return false;

	for (k = 1; k < LANGUAGE_MAX_VALUE && (iter = this->m_spData->find(k)) != this->m_spData->end(); k ++);

	if (k >= LANGUAGE_MAX_VALUE) {
		this->m_kLangKey = 0;

		return false;
	}

	this->m_kLangKey = k;

	return true;
}

Config* PSChooseLanguage::isLangAvailable(const char *cpcLang) {
	Manager *pManager;
	Container c;

	if (cpcLang == nullptr || this->m_spPipeline.get() == nullptr || (pManager = this->m_spPipeline->getManager()) == nullptr)
		return false;

	c.setData(shared_ptr<Comparable>(new Config(cpcLang, nullptr)));

	return dynamic_cast<Config *>(pManager->get(c));
}