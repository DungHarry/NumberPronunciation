/*
    Author: Dung Ly Viet
    Date created: September 5th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the source code file of the PSReadConfigs class in C++ programming language
*/

#include "ps_read_configs.h"

PSReadConfigs::PSReadConfigs() :
    PipelineState ()
{
    this->m_eStateType = PIPELINE_STATE_TYPE_READ_CONFIGS;
}

PSReadConfigs::PSReadConfigs(Pipeline *pPipeline, map<Key, shared_ptr<Base>> *pData, const char *cpcConfigFileName) :
    PipelineState(pPipeline, pData, PIPELINE_STATE_TYPE_READ_CONFIGS)
{
    this->m_upInternalData->at(PS_READ_CONFIGS_KEY_INPUT_CONFIG_NAME).reset(new StringData(cpcConfigFileName));
}

PSReadConfigs::~PSReadConfigs() {

}

bool PSReadConfigs::execute() {

}

const char* PSReadConfigs::getConfigFileName() {
    StringData *pStringData = dynamic_cast<StringData *>(this->m_upInternalData->at(PS_READ_CONFIGS_KEY_INPUT_CONFIG_NAME).get());

    return pStringData == nullptr ? nullptr : pStringData->getValue();
}

void PSReadConfigs::setConfigFileName(const char *cpcConfigFileName) {
    this->m_upInternalData->at(PS_READ_CONFIGS_KEY_INPUT_CONFIG_NAME).reset(new StringData(cpcConfigFileName));
}
