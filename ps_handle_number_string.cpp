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
	Date created: September 8th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the PSHandleNumberString class in C++ programming language
*/

#include "pipeline.h"
#include "ps_handle_number_string.h"

PSHandleNumberString::PSHandleNumberString() :
	PipelineState(),
	m_eNextState (PIPELINE_STATE_TYPE_NONE)
{
	this->m_eStateType = PIPELINE_STATE_TYPE_HANDLE_NUMBER_STRING;

	this->constructPossibleStates();
	this->determineNumberKey();

	if (this->m_spData.get() != nullptr)
		(*(this->m_spData.get()))[this->m_kNumberKey] = shared_ptr<Base>(nullptr);
}

PSHandleNumberString::PSHandleNumberString(shared_ptr<Pipeline> pipeline, shared_ptr<map<Key, shared_ptr<Base>>> data) :
	PipelineState(pipeline, data, PIPELINE_STATE_TYPE_HANDLE_NUMBER_STRING),
	m_eNextState (PIPELINE_STATE_TYPE_NONE)
{
	this->constructPossibleStates();
	this->determineNumberKey();

	if (this->m_spData.get() != nullptr)
		(*(this->m_spData.get()))[this->m_kNumberKey] = shared_ptr<Base>(nullptr);
}

PSHandleNumberString::~PSHandleNumberString() {

}

bool PSHandleNumberString::execute() {
	const char *cpcNumberString = nullptr;
	Number *pNumber;
	Config *pConfig = nullptr;

	if (NumberHandler::getInstance() == nullptr || this->m_spData.get() == nullptr || this->m_spData->find(this->m_kNumberKey) == this->m_spData->end() || (cpcNumberString = this->getNumberString()) == nullptr || (pConfig = this->getConfig()) == nullptr) {
		this->m_eNextState = PIPELINE_STATE_TYPE_FINISH;
		
		return false;
	}

	NumberHandler::getInstance()->setNumberString(cpcNumberString);
	NumberHandler::getInstance()->setConfig(pConfig);

	if (NumberHandler::getInstance()->execute() == false || (pNumber = NumberHandler::getInstance()->releaseNumber()) == nullptr) {
		this->m_eNextState = PIPELINE_STATE_TYPE_FINISH;

		return false;
	}

	this->m_spData->at(this->m_kNumberKey).reset(pNumber);

	this->m_eNextState = PIPELINE_STATE_TYPE_HANDLE_PRONUNCIATION;

	return true;
}

PipelineStateType PSHandleNumberString::determineNextStateType() const {
	return this->m_eNextState;
}

bool PSHandleNumberString::cleanup() {
	if (this->m_spData.get() == nullptr || this->m_spData->find(this->m_kNumberKey) == this->m_spData->end())
		return false;

	this->m_spData->at(this->m_kNumberKey).reset();

	return true;
}

Key PSHandleNumberString::getNumberKey() {
	return this->m_kNumberKey;
}

bool PSHandleNumberString::constructPossibleStates() {
	if (this->m_upPossibleStates.get() == nullptr)
		return false;

	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_FINISH);
	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_HANDLE_PRONUNCIATION);

	return true;
}

bool PSHandleNumberString::determineNumberKey() {
	PSInputNumberString *pInputNumberString;

	if (this->m_spPipeline.get() == nullptr || (pInputNumberString = dynamic_cast<PSInputNumberString *>(this->m_spPipeline->getStateByKey(PIPELINE_STATE_TYPE_INPUT_NUMBER_STRING))) == nullptr) {
		this->m_kNumberKey = -2;
		
		return false;
	}

	this->m_kNumberKey = pInputNumberString->getNumberStringKey() > 0 && pInputNumberString->getNumberStringKey() < LANGUAGE_MAX_VALUE - 1 ? pInputNumberString->getNumberStringKey() + 1 : pInputNumberString->getNumberStringKey() - 1;

	return true;
}

const char* PSHandleNumberString::getNumberString() {
	PSInputNumberString *pInputNumberString;
	StringData *pNumberStringData = nullptr;

	if (this->m_spPipeline.get() == nullptr || (pInputNumberString = dynamic_cast<PSInputNumberString *>(this->m_spPipeline->getStateByKey(PIPELINE_STATE_TYPE_INPUT_NUMBER_STRING))) == nullptr || this->m_spData.get() == nullptr || this->m_spData->find(pInputNumberString->getNumberStringKey()) == this->m_spData->end() || (pNumberStringData = dynamic_cast<StringData *>(this->m_spData->at(pInputNumberString->getNumberStringKey()).get())) == nullptr)
		return nullptr;

	return pNumberStringData->getValue();
}

Config* PSHandleNumberString::getConfig() {
	PSChooseLanguage *pChooseLangPipeline;
	Container c;
	StringData *psLang = nullptr;
	Config *pConfig;
    shared_ptr<Comparable> spConfig (nullptr);

	if (this->m_spPipeline.get() == nullptr || (pChooseLangPipeline = dynamic_cast<PSChooseLanguage *>(this->m_spPipeline->getStateByKey(PIPELINE_STATE_TYPE_CHOOSE_LANG))) == nullptr || this->m_spData.get() == nullptr || this->m_spData->find(pChooseLangPipeline->getLangKey()) == this->m_spData->end() || (psLang = dynamic_cast<StringData *>(this->m_spData->at(pChooseLangPipeline->getLangKey()).get())) == nullptr || this->m_spPipeline->getManager() == nullptr)
		return nullptr;

    spConfig.reset(new Config(psLang->getValue(), nullptr));

    c.setData(spConfig);

	if ((pConfig = dynamic_cast<Config *>(this->m_spPipeline->getManager()->get(c))) == nullptr)
		return nullptr;

	return pConfig;
}
