/*
	Author: Dung Ly Viet
	Date created: September 1st, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the PipelineState class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_PIPELINE_STATE_H_
#define _COC_COC_NUMBER_PRONUNCIATION_PIPELINE_STATE_H_

#include <map>
#include <memory>
#include <set>
#include "handler.h"
#include "executable.h"
#include "data.h"
#include "comparable.h"
#include "pipeline.h"
#include "cleanupable.h"

class Pipeline;

class PipelineState : public Base, public Executable, public Comparable, public Cleanupable {
public:
	PipelineState();
    PipelineState(shared_ptr<Pipeline> pipeline, shared_ptr<map<Key, shared_ptr<Base>>> data, PipelineStateType eStateType);
	virtual ~PipelineState();

	virtual bool execute();

    PipelineStateType getStateType() const;
	void setStateType(const PipelineStateType eState);

	set<PipelineStateType>* getPossibleStates();

	map<Key, shared_ptr<Base>>* getData();
	void setData(map<Key, shared_ptr<Base>> *pData);

    map<Key, unique_ptr<Data>>* getInternalData();

	virtual bool less(const Comparable &com);
	virtual bool equal(const Comparable &com);

	virtual bool isValidState(const PipelineStateType eType) const;

	virtual PipelineStateType determineNextStateType() const;

	virtual bool cleanup();
protected:
	PipelineStateType m_eStateType;
	unique_ptr<set<PipelineStateType>> m_upPossibleStates;
	shared_ptr<map<Key, shared_ptr<Base>>> m_spData;
    unique_ptr<map<Key, unique_ptr<Data>>> m_upInternalData;
    shared_ptr<Pipeline> m_spPipeline;

private:
	virtual bool constructPossibleStates();
};

#endif