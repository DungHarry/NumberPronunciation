/*
    Author: Dung Harry
    Date created: September 5th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the PSReadConfigs class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_PS_READ_CONFIGS_H_
#define _COC_COC_NUMBER_PRONUNCIATION_PS_READ_CONFIGS_H_

#include "string_data.h"
#include "wstring_data.h"
#include "pipeline_state.h"
#include "config_name_parser.h"
#include "file_handler.h"

class Pipeline;

#define PS_READ_CONFIGS_KEY_INPUT_CONFIG_NAME (static_cast<int32_t>(1 << 14))

class PSReadConfigs : public PipelineState {
public:
    PSReadConfigs();
    PSReadConfigs(shared_ptr<Pipeline> pipeline, shared_ptr<map<Key, shared_ptr<Base>>> data, const char *cpcConfigFileName);
    virtual ~PSReadConfigs();

    virtual bool execute();

    const char* getConfigFileName();
    void setConfigFileName(const char *cpcConfigFileName);

	virtual PipelineStateType determineNextStateType() const;

	virtual bool cleanup();
protected:
	PipelineStateType m_eNextState;

private:
	virtual bool constructPossibleStates();
};

#endif
