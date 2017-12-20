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
	Date created: September 7th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the PSInputNumberString class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_PS_INPUT_NUMBER_STRING_H_
#define _COC_COC_NUMBER_PRONUNCIATION_PS_INPUT_NUMBER_STRING_H_

#include <iostream>
#include "pipeline_state.h"
#include "ps_help.h"
#include "standard_io_utility.h"
#include "ps_choose_lang.h"
#include "string_utility.h"
#include "input_exception.h"

class Pipeline;

#define PS_INPUT_NUMBER_STRING_MAX_TRIES_DEFAULT_VALUE (static_cast<int16_t>(3))

class PSInputNumberString : public PipelineState {
public:
	PSInputNumberString();
	PSInputNumberString(shared_ptr<Pipeline> pipeline, shared_ptr<map<Key, shared_ptr<Base>>> data, const int16_t iMaxTries);
	virtual ~PSInputNumberString();

	virtual bool execute();

	virtual PipelineStateType determineNextStateType() const;

	virtual bool cleanup();

	Key getNumberStringKey();

	int16_t getMaxTries();
	void setMaxTries(const int16_t iMaxTries);

	int16_t getTryCount();
	void setTryCount(const int16_t iTryCount);
protected:
	PipelineStateType m_eNextState;
	Key m_kNumberStringKey;
	int16_t m_iTryCount;
	int16_t m_iMaxTries;

private:
	virtual bool constructPossibleStates();

	bool determineNumberStringKey();
};

#endif
