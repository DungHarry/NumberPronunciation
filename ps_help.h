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

	Description: this is the header file of the PSHelp class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_PS_HELP_H_
#define _COC_COC_NUMBER_PRONUNCIATION_PS_HELP_H_

#include <iostream>
#include "pipeline_state.h"
#include "ps_choose_lang.h"
#include "config.h"
#include "string_data.h"
#include "normal_digit_attribute.h"
#include "special_digit_attribute.h"

class Pipeline;

enum PSHelpType {
	PS_HELP_TYPE_NONE = 0,
	PS_HELP_TYPE_LANG,
	PS_HELP_TYPE_NUMBER_STRING,
	PS_HELP_TYPE_COUNT
};

class PSHelp : public PipelineState {
public:
	PSHelp();
	PSHelp(PSHelpType eHelpType, shared_ptr<Pipeline> pipeline, shared_ptr<map<Key, shared_ptr<Base>>> data);
	virtual ~PSHelp();

	virtual bool execute();

	virtual PipelineStateType determineNextStateType() const;

	virtual bool cleanup();

	PSHelpType getHelpType();
	void setHelpType(const PSHelpType eHelpType);
protected:
	PipelineStateType m_eNextState;
	PSHelpType m_eHelpType;

private:
	virtual bool constructPossibleStates();

	void displayHelpLang();
	void displayHelpNumberString();
};

#endif
