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

    Description: this is the source code file of the PSReadConfigs class in C++ programming language
*/

#include "ps_read_configs.h"
#include "pipeline.h"

PSReadConfigs::PSReadConfigs() :
    PipelineState (),
	m_eNextState (PIPELINE_STATE_TYPE_FINISH)
{
    this->m_eStateType = PIPELINE_STATE_TYPE_READ_CONFIGS;

	this->constructPossibleStates();
}

PSReadConfigs::PSReadConfigs(shared_ptr<Pipeline> pipeline, shared_ptr< map< Key, shared_ptr< Base > > > data, const char *cpcConfigFileName) :
	PipelineState(pipeline, data, PIPELINE_STATE_TYPE_READ_CONFIGS),
	m_eNextState (PIPELINE_STATE_TYPE_FINISH)
{
    (*(this->m_upInternalData.get()))[PS_READ_CONFIGS_KEY_INPUT_CONFIG_NAME] = unique_ptr<Data>(new StringData(cpcConfigFileName));

	this->constructPossibleStates();
}

PSReadConfigs::~PSReadConfigs() {

}

bool PSReadConfigs::execute() {
	StringData *pFileNameData;
	vector<ConfigName<wchar_t> *> *pConfigNames;
	int32_t i;

	if (ConfigNameParser::getInstance() == nullptr || FileHandler::getInstance() == nullptr || (pFileNameData = dynamic_cast<StringData *>(this->m_upInternalData->at(PS_READ_CONFIGS_KEY_INPUT_CONFIG_NAME).get())) == nullptr || pFileNameData->getValue() == nullptr || this->m_spData.get() == nullptr) {
		this->m_eNextState = PIPELINE_STATE_TYPE_FINISH;
		
		return false;
    }

	FileHandler::getInstance()->setFileName(pFileNameData->getValue());
	FileHandler::getInstance()->setType(FILE_HANDLER_TYPE_READ);

	if (FileHandler::getInstance()->execute() == false || FileHandler::getInstance()->getBufferContent() == nullptr) {
		this->m_eNextState = PIPELINE_STATE_TYPE_FINISH;
		
		return false;
    }

	ConfigNameParser::getInstance()->setBuffer(FileHandler::getInstance()->getBufferContent());

	if (ConfigNameParser::getInstance()->execute() == false || (pConfigNames = ConfigNameParser::getInstance()->releaseConfigNames()) == nullptr) {
		this->m_eNextState = PIPELINE_STATE_TYPE_FINISH;
		
		return false;
    }

	for (i = 0; i < pConfigNames->size(); i ++)
		if (*(pConfigNames->data() + i) != nullptr)
			(*(this->m_spData.get()))[(*(pConfigNames->data() + i))->getId()] = shared_ptr<Base>(*(pConfigNames->data() + i));

	pConfigNames->clear();
	delete pConfigNames;

	this->m_eNextState = PIPELINE_STATE_TYPE_PARSE_CONFIGS;

	return true;
}

const char* PSReadConfigs::getConfigFileName() {
    StringData *pStringData = dynamic_cast<StringData *>(this->m_upInternalData->at(PS_READ_CONFIGS_KEY_INPUT_CONFIG_NAME).get());

    return pStringData == nullptr ? nullptr : pStringData->getValue();
}

void PSReadConfigs::setConfigFileName(const char *cpcConfigFileName) {
    this->m_upInternalData->at(PS_READ_CONFIGS_KEY_INPUT_CONFIG_NAME).reset(new StringData(cpcConfigFileName));
}

PipelineStateType PSReadConfigs::determineNextStateType() const {
	return this->m_eNextState; 
}

bool PSReadConfigs::cleanup() {
	Key k;

	if (this->m_spData.get() == nullptr)
		return false;

	for (k = 1; k < LANGUAGE_MAX_VALUE && this->m_spData->find(k) != this->m_spData->end(); k ++)
		if (this->m_spData->at(k).get() != nullptr)
			this->m_spData->at(k).reset();

	return true;
}

bool PSReadConfigs::constructPossibleStates() {
	if (this->m_upPossibleStates.get() == nullptr)
		return false;
	
	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_FINISH);
	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_PARSE_CONFIGS);

	return true;
}
