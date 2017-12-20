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

	Description: this is the source code file of the PSOutputPronunciation class in C++ programming language
*/

#include "ps_output_pronunciation.h"
#include "pipeline.h"

PSOutputPronunciation::PSOutputPronunciation() :
	PipelineState (),
	m_eNextState (PIPELINE_STATE_TYPE_NONE)
{
	this->m_eStateType = PIPELINE_STATE_TYPE_OUTPUT_PRONUNCIATION;

	this->constructPossibleStates();
}

PSOutputPronunciation::PSOutputPronunciation(shared_ptr<Pipeline> pipeline, shared_ptr<map<Key, shared_ptr<Base>>> data) :
	PipelineState (pipeline, data, PIPELINE_STATE_TYPE_OUTPUT_PRONUNCIATION),
	m_eNextState (PIPELINE_STATE_TYPE_NONE)
{
	this->constructPossibleStates();
}

PSOutputPronunciation::~PSOutputPronunciation() {

}

bool PSOutputPronunciation::execute() {
	WStringData *pPronunciation;

	if ((pPronunciation = this->getPronunciationString()) == nullptr) {
		this->m_eNextState = PIPELINE_STATE_TYPE_FINISH;
		
		return false;
	}

	wcout << L"Output: " << pPronunciation->getValue() << endl;

	this->m_eNextState = PIPELINE_STATE_TYPE_FINISH;

	return true;
}

PipelineStateType PSOutputPronunciation::determineNextStateType() const {
	return this->m_eNextState;
}

bool PSOutputPronunciation::cleanup() {
	return true;
}

bool PSOutputPronunciation::constructPossibleStates() {
	if (this->m_upPossibleStates.get() == nullptr)
		return false;

	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_FINISH);

	return true;
}

WStringData* PSOutputPronunciation::getPronunciationString() {
	PSHandlePronunciation *pHandlePronunciationPipelineState;
	WStringData *pResult;

	if (this->m_spPipeline.get() == nullptr || (pHandlePronunciationPipelineState = dynamic_cast<PSHandlePronunciation *>(this->m_spPipeline->getStateByKey(PIPELINE_STATE_TYPE_HANDLE_PRONUNCIATION))) == nullptr || this->m_spData.get() == nullptr || (pResult = dynamic_cast<WStringData *>(this->m_spData->at(pHandlePronunciationPipelineState->getPronunciationKey()).get())) == nullptr)
		return nullptr;

	return pResult;
}
