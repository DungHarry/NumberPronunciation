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
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the global definitions in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_GLOBAL_H_
#define _COC_COC_NUMBER_PRONUNCIATION_GLOBAL_H_

#include <cstdint>

using namespace std;

#define NUMBER_UNIT_MAX_DIGITS_VALUE (static_cast<int32_t>(3))
#define LANGUAGE_MAX_VALUE (static_cast<int32_t>(1 << 10))

typedef int32_t PipelineStateKey;
typedef int32_t Key;

enum ObjectType {
	OBJECT_TYPE_NONE = 0,
	OBJECT_TYPE_NORMAL_DIGIT,
	OBJECT_TYPE_SPECIAL_DIGIT,
	OBJECT_TYPE_CONFIG,
	OBJECT_TYPE_NUMBER,
    OBJECT_TYPE_CONFIG_FILE,
	OBJECT_TYPE_COUNT
};

enum AttributeType {
	ATTRIBUTE_TYPE_NONE = 0,
	ATTRIBUTE_TYPE_NORMAL_DIGIT,
	ATTRIBUTE_TYPE_SPECIAL_DIGIT,
	ATTRIBUTE_TYPE_CONDITION_DIGIT,
	ATTRIBUTE_TYPE_CONDITION_APPEND,
    ATTRIBUTE_TYPE_CONDITION_APPEND_DIGITS_END,
    ATTRIBUTE_TYPE_MULTIPLE_DIGITS,
	ATTRIBUTE_TYPE_COUNT
};

enum HandlerType {
    HANDLER_TYPE_NONE = 0,
    HANDLER_TYPE_FILE,
    HANDLER_TYPE_PARSE,
    HANDLER_TYPE_LOCALE,
    HANDLER_TYPE_NUMBER,
	HANDLER_TYPE_PRONUNCIATION,
	HANDLER_TYPE_PIPELINE,
    HANDLER_TYPE_CONFIG_NAME_PARSE,
    HANDLER_TYPE_COUNT,
};

enum UtilityType {
    UTILITY_TYPE_NONE = 0,
    UTILITY_TYPE_STRING,
    UTILITY_TYPE_STREAM,
	UTILITY_TYPE_SEARCH,
	UTILITY_TYPE_CONFIG,
	UTILITY_TYPE_STANDARD_IO,
	UTILITY_TYPE_COUNT
};

enum ExceptionType {
	EXCEPTION_TYPE_NONE = 0,
	EXCEPTION_TYPE_NUMBER,
    EXCEPTION_TYPE_INPUT,
	EXCEPTION_TYPE_COUNT
};

enum DataType {
	DATA_TYPE_NONE = 0,
    DATA_TYPE_STRING,
    DATA_TYPE_WSTRING,
	DATA_TYPE_WRAPPER,
	DATA_TYPE_COUNT
};

enum PipelineStateType {
	PIPELINE_STATE_TYPE_NONE = 0,
	PIPELINE_STATE_TYPE_READ_CONFIGS,
	PIPELINE_STATE_TYPE_PARSE_CONFIGS,
	PIPELINE_STATE_TYPE_CHOOSE_LANG,
	PIPELINE_STATE_TYPE_INPUT_NUMBER_STRING,
	PIPELINE_STATE_TYPE_HANDLE_NUMBER_STRING,
	PIPELINE_STATE_TYPE_HANDLE_PRONUNCIATION,
	PIPELINE_STATE_TYPE_OUTPUT_PRONUNCIATION,
	PIPELINE_STATE_TYPE_HELP,
	PIPELINE_STATE_TYPE_FINISH,
	PIPELINE_STATE_TYPE_COUNT
};

enum DeleterType {
    DELETER_TYPE_NONE = 0,
    DELETER_TYPE_NORMAL,
    DELETER_TYPE_NULL,
    DELETER_TYPE_COUNT
};

#endif
