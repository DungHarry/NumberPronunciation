/*
	Author: Dung Ly Viet
	Date created: August 17th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the Attribute class in C++ programming language
*/

#ifndef _COC_COC_NUMBER_PRONUNCIATION_ATTRIBUTE_H_
#define _COC_COC_NUMBER_PRONUNCIATION_ATTRIBUTE_H_

#include "global.h"
#include "base.h"
#include "comparable.h"
#include <memory>

#define ATTRIBUTE_ID_INVALID_VALUE (static_cast<int16_t>(-1))

class Attribute : public Base, public Comparable {
public:
	Attribute();
	Attribute(int16_t iId, AttributeType eType);
	virtual ~Attribute();

	virtual AttributeType getType();
	virtual void setType(const AttributeType eType);

	virtual int16_t getId();
	virtual void setId(const int16_t iId);

	virtual bool less(const Comparable &attr);
	virtual bool equal(const Comparable &attr);
protected:
	AttributeType m_eType;
	int16_t m_iId;
};

#endif
