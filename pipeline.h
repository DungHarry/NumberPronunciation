/*
    NumberPronunciation provides a way to pronounce a number
    Copyright (C) 2017 of Dung Harry

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.

    Author: Dung Harry
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
#include "null_deleter.h"
#include "normal_deleter.h"

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
