/*
	Author: Dung Ly Viet
	Date created: August 31th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Pipeline class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_PIPELINE_H_
#define _COC_COC_NUMBER_PRONUNCIATION_PIPELINE_H_

#include <vector>
#include <memory>
#include <set>
#include "handler.h"
#include "executable.h"
#include "data.h"

enum PipelineStateType {
	PIPELINE_STATE_TYPE_NONE = 0,
	PIPELINE_STATE_TYPE_COUNT
};

class PipelineState : public Base, public Executable {
public:
	PipelineState();
	PipelineState(PipelineStateType eStateType);

	virtual bool execute();

	bool switchToState();
protected:
	PipelineStateType m_eStateType;
	unique_ptr<set<PipelineState>> m_upPossibleStates;
	unique_ptr<vector<shared_ptr<Base>>> m_upData;
};

class Pipeline : public Handler, public Executable {
public:
	Pipeline();
	virtual ~Pipeline();



private:
	static unique_ptr<Pipeline> m_upInstance;
};

#endif