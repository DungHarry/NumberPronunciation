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
    Date created: September 3rd, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the ConfigNameParser class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_CONFIG_NAME_PARSER_H_
#define _COC_COC_NUMBER_PRONUNCIATION_CONFIG_NAME_PARSER_H_

#include <memory>
#include <vector>
#include "handler.h"
#include "config_name.h"
#include "stream_utility.h"
#include "string_utility.h"

#define CONFIG_NAME_PARSER_BUFFER_LENGTH (static_cast<int32_t>(1 << 12))

class ConfigNameParser : public Handler {
public:
    ConfigNameParser();
    ConfigNameParser(const wchar_t *cpwcBuffer);
    virtual ~ConfigNameParser();

    virtual bool execute();

    vector<ConfigName<wchar_t> *> *releaseConfigNames();

    const wchar_t* getBuffer();
    void setBuffer(const wchar_t *cpwcBuffer);

    static ConfigNameParser* getInstance();
protected:
    unique_ptr<vector<ConfigName<wchar_t> *>> m_upConfigNames;
    unique_ptr<wstring> m_upwsBuffer;

    virtual bool parseLine(const wchar_t *cpwcLine);
private:
    static unique_ptr<ConfigNameParser> m_upInstance;
};

#endif
