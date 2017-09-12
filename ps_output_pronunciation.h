/*
	Author: Dung Ly Viet
	Date created: September 8th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the PSOutputPronunciation class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_PS_OUTPUT_PRONUNCIATION_H_
#define _COC_COC_NUMBER_PRONUNCIATION_PS_OUTPUT_PRONUNCIATION_H_

#include "pipeline_state.h"
#include "ps_handle_pronunciation.h"
#include "standard_io_utility.h"

class PipelineState;

class PSOutputPronunciation : public PipelineState {
public:
	PSOutputPronunciation();
	PSOutputPronunciation(shared_ptr<Pipeline> pipeline, shared_ptr<map<Key, shared_ptr<Base>>> data);
	virtual ~PSOutputPronunciation();

	virtual bool execute();

	virtual PipelineStateType determineNextStateType() const;

	virtual bool cleanup();
protected:
	PipelineStateType m_eNextState;
private:
	virtual bool constructPossibleStates();

	WStringData* getPronunciationString();
};

#endif