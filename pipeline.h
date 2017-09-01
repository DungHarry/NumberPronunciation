/*
	Author: Dung Ly Viet
	Date created: August 31th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Pipeline class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_PIPELINE_H_
#define _COC_COC_NUMBER_PRONUNCIATION_PIPELINE_H_

#include <map>
#include <memory>
#include "pipeline_state.h"
#include "container.h"
#include "handler.h"
#include "data.h"

class Pipeline : public Handler, public Executable {
public:
	Pipeline();
	Pipeline(const PipelineStateType eCurrentState);
	virtual ~Pipeline();

	virtual bool execute();

	map<PipelineStateKey, PipelineState*>* getStates();

	PipelineStateType getCurrentState();
	void setCurrentState(const PipelineStateType eState);

	map<Key, shared_ptr<Base>>* getData();

	static Pipeline* getInstance();
protected:
	PipelineStateType m_eCurrentState;
	unique_ptr<map<PipelineStateKey, PipelineState*>> m_upStates;
	shared_ptr<map<Key, shared_ptr<Base>>> m_spData;

private:
	virtual bool determineNextState();

	int32_t doBinarySearch();

	static unique_ptr<Pipeline> m_upInstance;
};

#endif