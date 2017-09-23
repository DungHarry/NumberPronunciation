/*
    Author: Dung Harry
	Date created: September 8th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the PSHandlePronunciation class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_HANDLE_PRONUNCIATION_H_
#define _COC_COC_NUMBER_PRONUNCIATION_HANDLE_PRONUNCIATION_H_

#include "wstring_data.h"
#include "pipeline_state.h"
#include "ps_handle_number_string.h"
#include "ps_choose_lang.h"
#include "pronunciation_handler.h"

class Pipeline;

class PSHandlePronunciation : public PipelineState {
public:
	PSHandlePronunciation();
	PSHandlePronunciation(shared_ptr<Pipeline> pipeline, shared_ptr<map<Key, shared_ptr<Base>>> data);
	virtual ~PSHandlePronunciation();

	virtual bool execute();

	virtual PipelineStateType determineNextStateType() const;

	virtual bool cleanup();

	Key getPronunciationKey();
protected:
	PipelineStateType m_eNextState;
	Key m_kPronunciationKey;

private:
	virtual bool constructPossibleStates();

	bool determinePronunciationKey();

	Config* getConfig();
	Number* getNumber();
};

#endif
