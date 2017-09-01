/*
	Author: Dung Ly Viet
	Date created: September 1st, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the PipelineState class in C++ programming language
*/

#include "pipeline_state.h"

PipelineState::PipelineState() :
	m_eStateType (PIPELINE_STATE_TYPE_NONE),
	m_upPossibleStates (new set<PipelineStateType>()),
	m_spData (nullptr)
{

}

PipelineState::PipelineState(PipelineStateType eStateType) :
	m_eStateType (eStateType <= PIPELINE_STATE_TYPE_NONE || eStateType >= PIPELINE_STATE_TYPE_COUNT ? PIPELINE_STATE_TYPE_NONE : eStateType),
	m_upPossibleStates (new set<PipelineStateType>()),
	m_spData (nullptr)
{

}

PipelineState::~PipelineState() {
	if (this->m_spData.get() != nullptr)
		this->m_spData.reset();

	if (this->m_upPossibleStates.get() != nullptr)
		this->m_upPossibleStates.reset();
}

bool PipelineState::execute() {
	return false;
}

PipelineStateType PipelineState::getStateType() const {
	return this->m_eStateType;
}

void PipelineState::setStateType(const PipelineStateType eState) {
	if (eState <= PIPELINE_STATE_TYPE_NONE || eState >= PIPELINE_STATE_TYPE_COUNT)
		return;

	this->m_eStateType = eState;
}

set<PipelineStateType>* PipelineState::getPossibleStates() {
	return this->m_upPossibleStates.get();
}

map<Key, shared_ptr<Base>>* PipelineState::getData() {
	return this->m_spData.get();
}

void PipelineState::setData(map<Key, shared_ptr<Base>> *pData) {
	this->m_spData.reset(pData);
}

bool PipelineState::less(const Comparable &com) {
	const PipelineState *pPipelineState = dynamic_cast<const PipelineState *>(&com);

	return (pPipelineState == nullptr) ? false : this->m_eStateType < pPipelineState->m_eStateType; 
}

bool PipelineState::equal(const Comparable &com) {
	const PipelineState *pPipelineState = dynamic_cast<const PipelineState *>(&com);

	return (pPipelineState == nullptr) ? false : this->m_eStateType == pPipelineState->m_eStateType;
}

bool PipelineState::isValidState(const PipelineStateType eType) const {
	set<PipelineStateType>::iterator iter;

	return (this->m_upPossibleStates.get() == nullptr || (iter = this->m_upPossibleStates->find(eType)) == this->m_upPossibleStates->end()) ? false : true;
}

PipelineStateType PipelineState::determineNextStateType() const {
	return this->m_eStateType;
}