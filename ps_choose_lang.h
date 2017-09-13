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
#include "ps_help.h"
#include "input_exception.h"

class Pipeline;

#define PS_CHOOSE_LANGUAGE_MAX_TRIES_DEFAULT_VALUE (static_cast<int16_t>(3))

class PSChooseLanguage : public PipelineState {
public:
	PSChooseLanguage();
	PSChooseLanguage(shared_ptr<Pipeline> pipeline, shared_ptr<map<Key, shared_ptr<Base>>> data, const int16_t iMaxTries);
	virtual ~PSChooseLanguage();

	virtual bool execute();

	virtual PipelineStateType determineNextStateType() const;

	virtual bool cleanup();

	Key getLangKey();

	int16_t getMaxTries();
	void setMaxTries(const int16_t iMaxTries);

	int16_t getTryCount();
	void setTryCount(const int16_t iTryCount);
protected:
	PipelineStateType m_eNextState;
	Key m_kLangKey;
	int16_t m_iTryCount;
	int16_t m_iMaxTries;

private:
	virtual bool constructPossibleStates();

	bool determineLangKey();
	Config* isLangAvailable(const char *cpcLang);
};

#endif
