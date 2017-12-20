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
	Date created: September 12th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the main source code file in C++ programming language
*/

#include <iostream>
#include "pipeline.h"
#include "number_exception.h"
#include "input_exception.h"
#include "locale_handler.h"

bool ensureLocale();

int32_t main(int argc, char** argv)
{   
	try {
        ensureLocale();

		Pipeline::getInstance()->execute();
    } catch(InputException &e) {
        wcout << e.what() << endl;
    } catch (NumberException &e) {
		wcout << e.what() << endl;
	} catch (Exception &e) {
		wcout << e.what() << endl;
	} catch (exception &e) {
		wcout << e.what() << endl;
	}

	return 0;
}

bool ensureLocale() {
    if(LocaleHandler::getInstance() == nullptr)
        return false;

    LocaleHandler::getInstance()->setScope(LOCALE_HANDLER_SCOPE_ALL);

    LocaleHandler::getInstance()->execute();

    return true;
}
