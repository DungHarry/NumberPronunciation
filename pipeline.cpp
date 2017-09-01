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
	m_eCurrentState (PIPELINE_STATE_TYPE_NONE),
	m_upStates(new map<int32_t, PipelineState*>()),
	m_spData (new map<int32_t, shared_ptr<Base>>())
{

}

Pipeline::Pipeline(const PipelineStateType eCurrentState) :
	Handler (HANDLER_TYPE_PIPELINE),
	m_eCurrentState (eCurrentState <= PIPELINE_STATE_TYPE_NONE || eCurrentState >= PIPELINE_STATE_TYPE_COUNT ? PIPELINE_STATE_TYPE_NONE : eCurrentState),
	m_upStates(new map<int32_t, PipelineState*>()),
	m_spData(new map<Key, shared_ptr<Base>>())
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

	while (this->m_eCurrentState != PIPELINE_STATE_FINISH) {
		if ((pPipelineState = this->m_upStates->at(static_cast<PipelineStateKey>(this->m_eCurrentState))) == nullptr) {
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

map<PipelineStateKey, PipelineState*>* Pipeline::getStates() {
	return this->m_upStates.get();
}

PipelineStateType Pipeline::getCurrentState() {
	return this->m_eCurrentState;
}

void Pipeline::setCurrentState(const PipelineStateType eType) {
	if (this->m_eCurrentState <= PIPELINE_STATE_TYPE_NONE || this->m_eCurrentState >= PIPELINE_STATE_TYPE_COUNT)
		return;

	this->m_eCurrentState = eType;
}

map<Key, shared_ptr<Base>>* Pipeline::getData() {
	return this->m_spData.get();
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

	if ((pPipelineState = this->m_upStates->at(static_cast<PipelineStateKey>(this->m_eCurrentState))) == nullptr || (eNextState = pPipelineState->determineNextStateType()) <= PIPELINE_STATE_TYPE_NONE || eNextState >= PIPELINE_STATE_TYPE_COUNT || pPipelineState->isValidState(eNextState) == false)
		return false;

	this->m_eCurrentState = eNextState;

	return true;
}