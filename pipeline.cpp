/*
	Author: Dung Ly Viet
	Date created: August 31th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the Pipeline class in C++ programming language
*/

#include "pipeline.h"

unique_ptr<Pipeline> Pipeline::m_upInstance (nullptr);

Pipeline::Pipeline() :
	Handler (HANDLER_TYPE_PIPELINE),
	m_iDataCount (static_cast<int32_t>(0)),
    m_ePreviousState (PIPELINE_STATE_TYPE_NONE),
	m_eCurrentState (PIPELINE_STATE_TYPE_NONE),
	m_upStates(new map<int32_t, unique_ptr<PipelineState>>()),
    m_spData (new map<int32_t, shared_ptr<Base>>()),
    m_upManager (new Manager())
{

}

Pipeline::Pipeline(const PipelineStateType eCurrentState) :
	Handler (HANDLER_TYPE_PIPELINE),
	m_iDataCount(static_cast<int32_t>(0)),
    m_ePreviousState (PIPELINE_STATE_TYPE_NONE),
	m_eCurrentState (eCurrentState <= PIPELINE_STATE_TYPE_NONE || eCurrentState >= PIPELINE_STATE_TYPE_COUNT ? PIPELINE_STATE_TYPE_NONE : eCurrentState),
	m_upStates(new map<int32_t, unique_ptr<PipelineState>>()),
    m_spData(new map<Key, shared_ptr<Base>>()),
    m_upManager (new Manager())
{

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
	PipelineState *pPipelineState;
	
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

int32_t Pipeline::getDataCount() {
	return this->m_iDataCount;
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
