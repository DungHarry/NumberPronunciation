/*
	Author: Dung Ly Viet
	Date created: September 8th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the PSHandleNumberString class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_PS_HANDLE_NUMBER_STRING_H_
#define _COC_COC_NUMBER_PRONUNCIATION_PS_HANDLE_NUMBER_STRING_H_

#include "pipeline_state.h"
#include "ps_input_number_string.h"
#include "number_handler.h"

class PSHandleNumberString : public PipelineState {
public:
	PSHandleNumberString(); 
	PSHandleNumberString(shared_ptr<Pipeline> pipeline, shared_ptr<map<Key, shared_ptr<Base>>> data);
	virtual ~PSHandleNumberString();

	virtual bool execute();

	virtual PipelineStateType determineNextStateType() const;

	virtual bool cleanup();

	Key getNumberKey();
protected:
	PipelineStateType m_eNextState;
	Key m_kNumberKey;

private:
	virtual bool constructPossibleStates();

	bool determineNumberKey();

	const char* getNumberString();
	Config* getConfig();
};

#endif