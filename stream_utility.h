/*
    Author: Dung Ly Viet
    Date created: August 23th, 2017
    Compiler: Visual C++ Compiler 2013

    Description: this is the header file of the StreamUtility class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_STREAM_UTILITY_H_
#define _COC_COC_NUMBER_PRONUNCIATION_STREAM_UTILITY_H_

#include "utility.h"
#include <string>
#include <memory>
#include <sstream>
#include <vector>

class StreamUtility : public Utility {
public:
    StreamUtility();
    StreamUtility(const wchar_t *pwcContent);
    virtual ~StreamUtility();

    wchar_t* readLine();
    wchar_t readCharacter();

    bool isEndOfStream();

    bool setContent(const wchar_t *pwcContent);

    bool clearContent();

    static StreamUtility* getInstance();
protected:
    auto_ptr<wstringstream> m_apStream;
private:
    static auto_ptr<StreamUtility> m_apInstance;
};

#endif
