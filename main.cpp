/*
	Author: Dung Ly Viet
	Date created: September 12th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the main source code file in C++ programming language
*/

#include <iostream>
#include "pipeline.h"
#include "number_exception.h"

int32_t main(int argc, char** argv)
{
	try {
		Pipeline::getInstance()->execute();
	} catch (NumberException &e) {
		wcout << e.what() << endl;
	} catch (Exception &e) {
		wcout << e.what() << endl;
	} catch (exception &e) {
		wcout << e.what() << endl;
	}

	return 0;
}

