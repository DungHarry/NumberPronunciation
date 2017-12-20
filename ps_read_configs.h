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
    Date created: September 5th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the PSReadConfigs class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_PS_READ_CONFIGS_H_
#define _COC_COC_NUMBER_PRONUNCIATION_PS_READ_CONFIGS_H_

#include "string_data.h"
#include "wstring_data.h"
#include "pipeline_state.h"
#include "config_name_parser.h"
#include "file_handler.h"

class Pipeline;

#define PS_READ_CONFIGS_KEY_INPUT_CONFIG_NAME (static_cast<int32_t>(1 << 14))

class PSReadConfigs : public PipelineState {
public:
    PSReadConfigs();
    PSReadConfigs(shared_ptr<Pipeline> pipeline, shared_ptr<map<Key, shared_ptr<Base>>> data, const char *cpcConfigFileName);
    virtual ~PSReadConfigs();

    virtual bool execute();

    const char* getConfigFileName();
    void setConfigFileName(const char *cpcConfigFileName);

	virtual PipelineStateType determineNextStateType() const;

	virtual bool cleanup();
protected:
	PipelineStateType m_eNextState;

private:
	virtual bool constructPossibleStates();
};

#endif
