/*
	Author: Dung Ly Viet
	Date created: August 31th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the Pipeline class in C++ programming language
*/

#include "pipeline.h"
#include "ps_choose_lang.h"
#include "ps_handle_number_string.h"
#include "ps_handle_pronunciation.h"
#include "ps_help.h"
#include "ps_input_number_string.h"
#include "ps_output_pronunciation.h"
#include "ps_parse_configs.h"
#include "ps_read_configs.h"

unique_ptr<Pipeline> Pipeline::m_upInstance (nullptr);

Pipeline::Pipeline() :
	Handler (HANDLER_TYPE_PIPELINE),
    m_ePreviousState (PIPELINE_STATE_TYPE_NONE),
	m_eCurrentState (PIPELINE_STATE_TYPE_NONE),
	m_upStates(new map<int32_t, unique_ptr<PipelineState>>()),
    m_spData (new map<int32_t, shared_ptr<Base>>()),
    m_upManager (new Manager(), ManagerDeleter())
{
	this->contructStates();
}

Pipeline::Pipeline(const PipelineStateType eCurrentState) :
	Handler (HANDLER_TYPE_PIPELINE),
    m_ePreviousState (PIPELINE_STATE_TYPE_NONE),
	m_eCurrentState (eCurrentState <= PIPELINE_STATE_TYPE_NONE || eCurrentState >= PIPELINE_STATE_TYPE_COUNT ? PIPELINE_STATE_TYPE_NONE : eCurrentState),
	m_upStates(new map<int32_t, unique_ptr<PipelineState>>()),
    m_spData(new map<Key, shared_ptr<Base>>()),
	m_upManager(new Manager(), ManagerDeleter())
{
	this->contructStates();
}

Pipeline::~Pipeline() {
    if (this->m_upStates.get() != nullptr) {
		this->m_upStates->clear();

		this->m_upStates.reset();
	}

	if (this->m_spData.get() != nullptr) {
		this->m_spData->clear();

		this->m_spData.reset();
    }
}

bool Pipeline::execute() {
	PipelineState *pPipelineState = nullptr;
	
	if (this->m_eCurrentState <= PIPELINE_STATE_TYPE_NONE || this->m_eCurrentState >= PIPELINE_STATE_TYPE_COUNT || this->m_upStates.get() == nullptr || this->m_upStates->size() <= 0)
		return false;

	while (this->m_eCurrentState != PIPELINE_STATE_TYPE_FINISH) {
		if (this->m_upStates->find(static_cast<PipelineStateKey>(this->m_eCurrentState)) == this->m_upStates->end() || (pPipelineState = this->m_upStates->at(static_cast<PipelineStateKey>(this->m_eCurrentState)).get()) == nullptr) {
			this->m_eCurrentState = PIPELINE_STATE_TYPE_NONE;

			return false;
		}

		if (pPipelineState->execute() == false) {
			this->m_eCurrentState = PIPELINE_STATE_TYPE_NONE;

			return false;
		}

		if (this->determineNextState() == false) {
			this->m_eCurrentState = PIPELINE_STATE_TYPE_NONE;

			return false;
		}
	}

	return true;
}

map<PipelineStateKey, unique_ptr<PipelineState>>* Pipeline::getStates() {
	return this->m_upStates.get();
}

PipelineStateType Pipeline::getCurrentState() {
	return this->m_eCurrentState;
}

void Pipeline::setCurrentState(const PipelineStateType eType) {
    if (eType <= PIPELINE_STATE_TYPE_NONE || eType >= PIPELINE_STATE_TYPE_COUNT)
		return;

	this->m_eCurrentState = eType;
}

PipelineStateType Pipeline::getPreviousState() {
    return this->m_ePreviousState;
}

void Pipeline::setPreviousState(const PipelineStateType eState) {
    if(eState < PIPELINE_STATE_TYPE_NONE || eState >= PIPELINE_STATE_TYPE_COUNT)
        return;

    this->m_ePreviousState = eState;
}

PipelineState* Pipeline::getStateByKey(const PipelineStateKey k) {
	return (this->m_upStates.get() == nullptr || this->m_upStates->find(k) == this->m_upStates->end()) ? nullptr : (*(this->m_upStates.get()))[k].get();
}

map<Key, shared_ptr<Base>>* Pipeline::getData() {
	return this->m_spData.get();
}

Manager* Pipeline::getManager() {
    return this->m_upManager.get();
}

Pipeline* Pipeline::getInstance() {
	if (m_upInstance.get() == nullptr)
		m_upInstance.reset(new Pipeline());

	return m_upInstance.get();
}

bool Pipeline::contructStates() {
	if (this->m_upStates.get() == nullptr)
		return false;

	if (this->m_upStates->find(PIPELINE_STATE_TYPE_READ_CONFIGS) != this->m_upStates->end())
		this->m_upStates->at(PIPELINE_STATE_TYPE_READ_CONFIGS).reset();

	(*(this->m_upStates.get()))[PIPELINE_STATE_TYPE_READ_CONFIGS] = move(unique_ptr<PipelineState>(new PSReadConfigs(shared_ptr<Pipeline>(this), this->m_spData, "config/locales.conf")));

	if (this->m_upStates->find(PIPELINE_STATE_TYPE_PARSE_CONFIGS) != this->m_upStates->end())
		this->m_upStates->at(PIPELINE_STATE_TYPE_PARSE_CONFIGS).reset();

	(*(this->m_upStates.get()))[PIPELINE_STATE_TYPE_PARSE_CONFIGS] = move(unique_ptr<PipelineState>(new PSParseConfigs(shared_ptr<Pipeline>(this), this->m_spData)));

	if (this->m_upStates->find(PIPELINE_STATE_TYPE_CHOOSE_LANG) != this->m_upStates->end())
		this->m_upStates->at(PIPELINE_STATE_TYPE_CHOOSE_LANG).reset();

	(*(this->m_upStates.get()))[PIPELINE_STATE_TYPE_CHOOSE_LANG] = move(unique_ptr<PipelineState>(new PSChooseLanguage(shared_ptr<Pipeline>(this), this->m_spData, PS_CHOOSE_LANGUAGE_MAX_TRIES_DEFAULT_VALUE)));
	
	if (this->m_upStates->find(PIPELINE_STATE_TYPE_INPUT_NUMBER_STRING) != this->m_upStates->end())
		this->m_upStates->at(PIPELINE_STATE_TYPE_INPUT_NUMBER_STRING).reset();
	
	(*(this->m_upStates.get()))[PIPELINE_STATE_TYPE_INPUT_NUMBER_STRING] = move(unique_ptr<PipelineState>(new PSInputNumberString(shared_ptr<Pipeline>(this), this->m_spData, PS_INPUT_NUMBER_STRING_MAX_TRIES_DEFAULT_VALUE)));
	
	if (this->m_upStates->find(PIPELINE_STATE_TYPE_HANDLE_NUMBER_STRING) != this->m_upStates->end())
		this->m_upStates->at(PIPELINE_STATE_TYPE_HANDLE_NUMBER_STRING).reset();

	(*(this->m_upStates.get()))[PIPELINE_STATE_TYPE_HANDLE_NUMBER_STRING] = move(unique_ptr<PipelineState>(new PSHandleNumberString(shared_ptr<Pipeline>(this), this->m_spData)));

	if (this->m_upStates->find(PIPELINE_STATE_TYPE_HANDLE_PRONUNCIATION) != this->m_upStates->end())
		this->m_upStates->at(PIPELINE_STATE_TYPE_HANDLE_PRONUNCIATION).reset();

	(*(this->m_upStates.get()))[PIPELINE_STATE_TYPE_HANDLE_PRONUNCIATION] = move(unique_ptr<PipelineState>(new PSHandlePronunciation(shared_ptr<Pipeline>(this), this->m_spData)));

	if (this->m_upStates->find(PIPELINE_STATE_TYPE_OUTPUT_PRONUNCIATION) != this->m_upStates->end())
		this->m_upStates->at(PIPELINE_STATE_TYPE_OUTPUT_PRONUNCIATION).reset();

	(*(this->m_upStates.get()))[PIPELINE_STATE_TYPE_OUTPUT_PRONUNCIATION] = move(unique_ptr<PipelineState>(new PSOutputPronunciation(shared_ptr<Pipeline>(this), this->m_spData)));

    if(this->m_upStates->find(PIPELINE_STATE_TYPE_HELP) != this->m_upStates->end())
        this->m_upStates->at(PIPELINE_STATE_TYPE_HELP).reset();

    (*(this->m_upStates.get()))[PIPELINE_STATE_TYPE_HELP] = move(unique_ptr<PipelineState>(new PSHelp(PS_HELP_TYPE_NONE, shared_ptr<Pipeline>(this), this->m_spData)));

	this->m_eCurrentState = PIPELINE_STATE_TYPE_READ_CONFIGS;
	this->m_ePreviousState = PIPELINE_STATE_TYPE_NONE; 

	return true;
}

bool Pipeline::determineNextState() {
	PipelineStateType eNextState;
	PipelineState *pPipelineState;

	if (this->m_eCurrentState <= PIPELINE_STATE_TYPE_NONE || this->m_eCurrentState >= PIPELINE_STATE_TYPE_COUNT || this->m_upStates.get() == nullptr)
		return false;

	if (this->m_upStates->find(static_cast<PipelineStateKey>(this->m_eCurrentState)) == this->m_upStates->end() || (pPipelineState = this->m_upStates->at(static_cast<PipelineStateKey>(this->m_eCurrentState)).get()) == nullptr || (eNextState = pPipelineState->determineNextStateType()) <= PIPELINE_STATE_TYPE_NONE || eNextState >= PIPELINE_STATE_TYPE_COUNT || pPipelineState->isValidState(eNextState) == false)
		return false;

    this->m_ePreviousState = this->m_eCurrentState;
	this->m_eCurrentState = eNextState;

	return true;
}
