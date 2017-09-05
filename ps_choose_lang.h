/*
	Author: Dung Ly Viet
	Date created: September 5th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the PSChooseLang class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_PS_CHOOSE_LANG_H_
#define _COC_COC_NUMBER_PRONUNCIATION_PS_CHOOSE_LANG_H_

#include <iostream>
#include "pipeline_state.h"
#include "locale_handler.h"
#include "standard_io_utility.h"
#include "string_data.h"
#include "config.h"

class PSChooseLanguage : public PipelineState {
public:
	PSChooseLanguage();
	PSChooseLanguage(Pipeline *pPipeline, map<Key, shared_ptr<Base>> *pData);
	virtual ~PSChooseLanguage();

	virtual bool execute();

	virtual PipelineStateType determineNextStateType() const;

	virtual bool cleanup();
protected:
	PipelineStateType m_eNextState;
	Key m_kLangKey;

private:
	virtual bool constructPossibleStates();

	bool determineLangKey();
	Config* isLangAvailable(const char *cpcLang);
};

#endif