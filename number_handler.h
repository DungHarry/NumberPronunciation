/*
    Author: Dung Ly Viet
    Date created: August 28th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the NumberHandler class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_NUMBER_HANDLER_H_
#define _COC_COC_NUMBER_PRONUNCIATION_NUMBER_HANDLER_H_

#include <memory>
#include <string>
#include <map>
#include "handler.h"
#include "normal_digit.h"
#include "special_digit.h"
#include "normal_digit_attribute.h"
#include "special_digit_attribute.h"
#include "number.h"
#include "config.h"

class NumberHandler : public Handler {
public:
    NumberHandler();
    NumberHandler(Config *pConfig, const char *cpcNumberString);
    virtual ~NumberHandler();

    virtual bool execute();

    Number* releaseNumber();

    Config* getConfig();
    void setConfig(Config *pConfig);

    string* getNumberString();
    void setNumberString(const char *cpcNumberString);

    bool isNumberStringValid();

    bool isNumberStringNegative();

    bool isNumberStringFloat();
protected:
    auto_ptr<Number> m_apNumber;
    shared_ptr<Config> m_spConfig;
    auto_ptr<string> m_apNumberString;

    bool preprocessStringNumber();
    char* getNumberStringNumericalPart();
    char* getNumberStringFloatingPointPart();
private:
	bool processSpecialDigit(char cSpecialDigit);
	bool processNumberString(const char *cpcNumberString);

    static auto_ptr<NumberHandler> m_apInstance;
};

#endif

