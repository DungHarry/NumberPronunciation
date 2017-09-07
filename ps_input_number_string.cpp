/*
	Author: Dung Ly Viet
	Date created: September 7th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the PSInputNumberString class in C++ programming language
*/

#include "ps_input_number_string.h"

PSInputNumberString::PSInputNumberString() :
	PipelineState(),
	m_eNextState (PIPELINE_STATE_TYPE_NONE),
	m_iMaxTries (PS_INPUT_NUMBER_STRING_MAX_TRIES_DEFAULT_VALUE),
	m_iTryCount (0)
{
	this->m_eStateType = PIPELINE_STATE_TYPE_INPUT_NUMBER_STRING;

	this->determineNumberStringKey();
	this->constructPossibleStates();
}

PSInputNumberString::PSInputNumberString(shared_ptr<Pipeline> pipeline, shared_ptr<map<Key, shared_ptr<Base>>> data, const int16_t iMaxTries) :
	PipelineState(pipeline, data, PIPELINE_STATE_TYPE_INPUT_NUMBER_STRING),
	m_eNextState (PIPELINE_STATE_TYPE_NONE),
	m_iMaxTries (iMaxTries),
	m_iTryCount (0)
{
	this->determineNumberStringKey();
	this->constructPossibleStates();
}

PSInputNumberString::~PSInputNumberString() {

}

bool PSInputNumberString::execute() {

}

PipelineStateType PSInputNumberString::determineNextStateType() const {
	if (this->m_eNextState == PIPELINE_STATE_TYPE_HELP) {

	}

	return this->m_eNextState;
}

bool PSInputNumberString::cleanup() {
	StringData *pStringNumber;

	if (this->m_spData.get() == nullptr)
		return false;

	if (this->m_spData->find(this->m_kNumberStringKey) != this->m_spData->end() && (pStringNumber = dynamic_cast<StringData *>((*(this->m_spData.get()))[this->m_kNumberStringKey].get())) != nullptr)
		(*(this->m_spData.get()))[this->m_kNumberStringKey].reset();

	this->m_iTryCount = 0;

	return true;
}

Key PSInputNumberString::getNumberStringKey() {
	return this->m_kNumberStringKey;
}

int16_t PSInputNumberString::getMaxTries() {
	return this->m_iMaxTries;
}

void PSInputNumberString::setMaxTries(const int16_t iMaxTries) {
	if (iMaxTries <= 0)
		return;

	this->m_iMaxTries = iMaxTries;
}

int16_t PSInputNumberString::getTryCount() {
	return this->m_iTryCount;
}

void PSInputNumberString::setTryCount(const int16_t iTryCount) {
	if (iTryCount <= 0)
		return;

	this->m_iTryCount = iTryCount;
}

bool PSInputNumberString::constructPossibleStates() {
	if (this->m_upPossibleStates.get() == nullptr)
		return false;

	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_FINISH);
	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_HELP);
	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_HANDLE_NUMBER_STRING);

	return true;
}

bool PSInputNumberString::determineNumberStringKey() {
	PSChooseLanguage *pChooseLanguage;

	if (this->m_spPipeline.get() == nullptr || (pChooseLanguage = dynamic_cast<PSChooseLanguage *>(this->m_spPipeline->getStateByKey(PIPELINE_STATE_TYPE_CHOOSE_LANG))) == nullptr)
		return false;

	this->m_kNumberStringKey = pChooseLanguage->getLangKey() > 0 && pChooseLanguage->getLangKey() < LANGUAGE_MAX_VALUE - 1 ? pChooseLanguage->getLangKey() + 1 : -1;

	return true;
}