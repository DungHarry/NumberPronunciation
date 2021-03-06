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
	Date created: September 5th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the PSChooseLang class in C++ programming language
*/

#include "pipeline.h"
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

PSChooseLanguage::PSChooseLanguage(shared_ptr<Pipeline> pipeline, shared_ptr< map< Key, shared_ptr< Base > > > data, const int16_t iMaxTries) :
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

}

bool PSChooseLanguage::execute() {
	char *pcBuffer;
	Config *pConfig;
	
	if (StandardIOUtility::getInstance() == nullptr || this->m_spData.get() == nullptr || this->m_spData->find(this->m_kLangKey) == this->m_spData->end() || this->m_iTryCount >= this->m_iMaxTries) {
        if(this->m_iTryCount >= this->m_iMaxTries)
            throw InputException(INPUT_EXCEPTION_REASON_EXCEED_TRY_COUNT);

        this->m_eNextState = PIPELINE_STATE_TYPE_FINISH;

		return false;
	}

	pcBuffer = new char[PS_CHOOSE_LANG_BUFFER_SIZE];

    wcout<<L"Enter the language: ";

	if (StandardIOUtility::getInstance()->readLine(pcBuffer, PS_CHOOSE_LANG_BUFFER_SIZE) == false) {
		this->m_eNextState = PIPELINE_STATE_TYPE_FINISH;
		this->m_iTryCount = 0;
		
		delete[] pcBuffer;
		
		return false;
	}

	if ((pConfig = this->isLangAvailable(pcBuffer)) == nullptr) {
		this->m_iTryCount ++;

		this->m_eNextState = PIPELINE_STATE_TYPE_HELP;

		delete[] pcBuffer;

        return true;
	}

	this->m_spData->at(m_kLangKey).reset(new StringData(pcBuffer));

	if (pConfig->getLang() != nullptr && pConfig->getLang()->getLocaleName() != nullptr) {
		LocaleHandler::getInstance()->setLocaleName(pConfig->getLang()->getLocaleName());
		LocaleHandler::getInstance()->setScope(LOCALE_HANDLER_SCOPE_ALL);
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

	if (this->m_spData.get() == nullptr) {
		this->m_kLangKey = 0;
		
		return false;
	}

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
    shared_ptr<Comparable> spConfig (nullptr);

	if (cpcLang == nullptr || this->m_spPipeline.get() == nullptr || (pManager = this->m_spPipeline->getManager()) == nullptr)
        return nullptr;

    spConfig.reset(new Config(cpcLang, nullptr));

    c.setData(spConfig);

    spConfig.reset();

	return dynamic_cast<Config *>(pManager->get(c));
}
