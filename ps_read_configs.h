/*
    Author: Dung Ly Viet
    Date created: September 5th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the PSReadConfigs class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_PS_READ_CONFIGS_H_
#define _COC_COC_NUMBER_PRONUNCIATION_PS_READ_CONFIGS_H_

#include "string_data.h"
#include "wstring_data.h"
#include "pipeline_state.h"

#define PS_READ_CONFIGS_KEY_INPUT_CONFIG_NAME (static_cast<int32_t>(1 << 10))

class PSReadConfigs : public PipelineState {
public:
    PSReadConfigs();
    PSReadConfigs(Pipeline *pPipeline, map<Key, shared_ptr<Base>> *pData, const char *cpcConfigFileName);
    virtual ~PSReadConfigs();

    virtual bool execute();

    const char* getConfigFileName();
    void setConfigFileName(const char *cpcConfigFileName);
};

#endif
