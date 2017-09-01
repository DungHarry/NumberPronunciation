/*
	Author: Dung Ly Viet
	Date created: September 1st, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the PipelineState class in C++ programming language
*/

#include <map>
#include <memory>
#include <set>
#include "handler.h"
#include "executable.h"
#include "data.h"
#include "comparable.h"

typedef int32_t PipelineStateKey;

enum PipelineStateType {
	PIPELINE_STATE_TYPE_NONE = 0,
	PIPELINE_STATE_FINISH,
	PIPELINE_STATE_TYPE_COUNT
};

class PipelineState : public Base, public Executable, public Comparable {
public:
	PipelineState();
	PipelineState(PipelineStateType eStateType);
	virtual ~PipelineState();

	virtual bool execute();

	PipelineStateType getStateType() const;
	void setStateType(const PipelineStateType eState);

	set<PipelineStateType>* getPossibleStates();

	map<Key, shared_ptr<Base>>* getData();
	void setData(map<Key, shared_ptr<Base>> *pData);

	virtual bool less(const Comparable &com);
	virtual bool equal(const Comparable &com);

	virtual bool isValidState(const PipelineStateType eType) const;

	virtual PipelineStateType determineNextStateType() const;
protected:
	PipelineStateType m_eStateType;
	unique_ptr<set<PipelineStateType>> m_upPossibleStates;
	shared_ptr<map<Key, shared_ptr<Base>>> m_spData;
};