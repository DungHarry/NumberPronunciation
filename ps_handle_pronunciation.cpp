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

	Description: this is the source code file of the PSHandlePronunciation class in C++ programming language
*/

#include "ps_handle_pronunciation.h"
#include "pipeline.h"

PSHandlePronunciation::PSHandlePronunciation() :
	PipelineState (),
	m_eNextState (PIPELINE_STATE_TYPE_NONE)
{
	this->m_eStateType = PIPELINE_STATE_TYPE_HANDLE_PRONUNCIATION;

	this->constructPossibleStates();
	this->determinePronunciationKey();

	if (this->m_spData.get() != nullptr)
		(*(this->m_spData.get()))[this->m_kPronunciationKey] = shared_ptr<Base>(nullptr);
}

PSHandlePronunciation::PSHandlePronunciation(shared_ptr<Pipeline> pipeline, shared_ptr< map< Key, shared_ptr< Base > > > data) :
	PipelineState (pipeline, data, PIPELINE_STATE_TYPE_HANDLE_PRONUNCIATION),
	m_eNextState (PIPELINE_STATE_TYPE_NONE)
{
	this->constructPossibleStates();
	this->determinePronunciationKey();
}

PSHandlePronunciation::~PSHandlePronunciation() {

}

bool PSHandlePronunciation::execute() {
	Number *pNumber;
	Config *pConfig;
	wstring *pwsPronunciation;

	if (this->m_spData.get() == nullptr || PronunciationHandler::getInstance() == nullptr || (pConfig = this->getConfig()) == nullptr || (pNumber = this->getNumber()) == nullptr) {
		this->m_eNextState = PIPELINE_STATE_TYPE_FINISH;
		
		return false;
	}

	PronunciationHandler::getInstance()->setConfig(pConfig);
	PronunciationHandler::getInstance()->setNumber(pNumber);

	if (PronunciationHandler::getInstance()->execute() == false || (pwsPronunciation = PronunciationHandler::getInstance()->getPronunciation()) == nullptr) {
		this->m_eNextState = PIPELINE_STATE_TYPE_FINISH;

		return false;
	}

	(*(this->m_spData.get()))[this->m_kPronunciationKey].reset(new WStringData(pwsPronunciation->c_str()));

	this->m_eNextState = PIPELINE_STATE_TYPE_OUTPUT_PRONUNCIATION;

	delete pwsPronunciation;

	return true;
}

PipelineStateType PSHandlePronunciation::determineNextStateType() const {
	return this->m_eNextState;
}

bool PSHandlePronunciation::cleanup() {
	if (this->m_spData.get() == nullptr || this->m_spData->find(this->m_kPronunciationKey) == this->m_spData->end())
		return false;

	this->m_spData->at(this->m_kPronunciationKey).reset();

	return true;
}

Key PSHandlePronunciation::getPronunciationKey() {
	return this->m_kPronunciationKey;
}

bool PSHandlePronunciation::constructPossibleStates() {
	if (this->m_upPossibleStates.get() == nullptr)
		return false;

	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_OUTPUT_PRONUNCIATION);
	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_FINISH);

	return true;
}

bool PSHandlePronunciation::determinePronunciationKey() {
	PSHandleNumberString *pHandleNumberStringPipeline;

	if (this->m_spPipeline.get() == nullptr || (pHandleNumberStringPipeline = dynamic_cast<PSHandleNumberString *>(this->m_spPipeline->getStateByKey(PIPELINE_STATE_TYPE_HANDLE_NUMBER_STRING))) == nullptr) {
		this->m_kPronunciationKey = -3;
		
		return false;
	}

	this->m_kPronunciationKey = pHandleNumberStringPipeline->getNumberKey() > 0 && pHandleNumberStringPipeline->getNumberKey() < LANGUAGE_MAX_VALUE - 1 ? pHandleNumberStringPipeline->getNumberKey() + 1 : pHandleNumberStringPipeline->getNumberKey() - 1;

	return true;
}

Config* PSHandlePronunciation::getConfig() {
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

Number* PSHandlePronunciation::getNumber() {
	PSHandleNumberString *pHandleNumberStringPipeline;
	Number *pNumber = nullptr;

	if (this->m_spPipeline.get() == nullptr || (pHandleNumberStringPipeline = dynamic_cast<PSHandleNumberString *>(this->m_spPipeline->getStateByKey(PIPELINE_STATE_TYPE_HANDLE_NUMBER_STRING))) == nullptr || this->m_spData.get() == nullptr || this->m_spData->find(pHandleNumberStringPipeline->getNumberKey()) == this->m_spData->end() || (pNumber = dynamic_cast<Number *>(this->m_spData->at(pHandleNumberStringPipeline->getNumberKey()).get())) == nullptr)
		return nullptr;

	return pNumber;
}
