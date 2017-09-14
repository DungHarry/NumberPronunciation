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
#include "manager.h"

class PipelineState;

class Pipeline : public Handler {
public:
	Pipeline();
	Pipeline(const PipelineStateType eCurrentState);
	virtual ~Pipeline();

	virtual bool execute();

	map<PipelineStateKey, unique_ptr<PipelineState>>* getStates();

	PipelineStateType getCurrentState();
	void setCurrentState(const PipelineStateType eState);

    PipelineStateType getPreviousState();
    void setPreviousState(const PipelineStateType eState);

	PipelineState* getStateByKey(const PipelineStateKey k);

	map<Key, shared_ptr<Base>>* getData();

    Manager* getManager();

	static Pipeline* getInstance();
protected:
	virtual bool contructStates();

    PipelineStateType m_ePreviousState;
	PipelineStateType m_eCurrentState;
	unique_ptr<map<PipelineStateKey, unique_ptr<PipelineState>>> m_upStates;
	shared_ptr< map< Key, shared_ptr< Base > > > m_spData;
    unique_ptr<Manager, ManagerDeleter> m_upManager;
private:
	virtual bool determineNextState();

	static unique_ptr<Pipeline> m_upInstance;
};

#endif
