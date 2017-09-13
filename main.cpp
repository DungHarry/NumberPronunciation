/*
	Author: Dung Ly Viet
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
