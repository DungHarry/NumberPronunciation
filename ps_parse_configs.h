/*
	Author: Dung Ly Viet
	Date created: September 5th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the PSParseConfigs class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_PS_PARSE_CONFIGS_H_
#define _COC_COC_NUMBER_PRONUNCIATION_PS_PARSE_CONFIGS_H_

#include "pipeline.h"
#include "pipeline_state.h"
#include "config_name.h"
#include "string_utility.h"
#include "file_handler.h"
#include "parse_handler.h"

class PSParseConfigs : public PipelineState {
public:
	PSParseConfigs();
	PSParseConfigs(Pipeline *pPipeline, map<Key, shared_ptr<Base>> *pData);
	virtual ~PSParseConfigs();

	virtual bool execute();

	virtual PipelineStateType determineNextStateType() const;

	virtual bool cleanup();
protected:
	PipelineStateType m_eNextState;

private:
	virtual bool constructPossibleStates();

	bool isConfigNameAvailable(const Key k);

	bool readConfigFile(ConfigName<wchar_t> *pwcConfigName);
	Config* parseConfigFile();
	bool addConfig(Manager *pManager, Config **pConfig);
};

#endif
