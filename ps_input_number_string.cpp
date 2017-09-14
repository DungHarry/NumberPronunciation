/*
	Author: Dung Ly Viet
	Date created: September 7th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the header file of the PSInputNumberString class in C++ programming language
*/

#include "ps_input_number_string.h"
#include "pipeline.h"

#define PS_INPUT_NUMBER_STRING_BUFFER_SIZE (static_cast<int32_t>(1 << 12))

PSInputNumberString::PSInputNumberString() :
	PipelineState(),
	m_eNextState (PIPELINE_STATE_TYPE_NONE),
	m_iMaxTries (PS_INPUT_NUMBER_STRING_MAX_TRIES_DEFAULT_VALUE),
	m_iTryCount (0)
{
	this->m_eStateType = PIPELINE_STATE_TYPE_INPUT_NUMBER_STRING;

	this->determineNumberStringKey();
	this->constructPossibleStates();

	if (this->m_spData.get() != nullptr)
		(*(this->m_spData.get()))[this->m_kNumberStringKey] = shared_ptr<Base>(new StringData()); 
}

PSInputNumberString::PSInputNumberString(shared_ptr<Pipeline> pipeline, shared_ptr<map<Key, shared_ptr<Base>>> data, const int16_t iMaxTries) :
	PipelineState(pipeline, data, PIPELINE_STATE_TYPE_INPUT_NUMBER_STRING),
	m_eNextState (PIPELINE_STATE_TYPE_NONE),
	m_iMaxTries (iMaxTries <= 0 ? PS_INPUT_NUMBER_STRING_MAX_TRIES_DEFAULT_VALUE : iMaxTries),
	m_iTryCount (0)
{
	this->determineNumberStringKey();
	this->constructPossibleStates();

	if (this->m_spData.get() != nullptr)
		(*(this->m_spData.get()))[this->m_kNumberStringKey] = shared_ptr<Base>(new StringData());
}

PSInputNumberString::~PSInputNumberString() {

}

bool PSInputNumberString::execute() {
	char *pcNumberStringBuffer;
	PSChooseLanguage *pChooseLangPipeline = nullptr;
	StringData *pLang = nullptr;
	Config *pConfig;
	Container c;
    shared_ptr<Comparable> spConfig;

	if (StandardIOUtility::getInstance() == nullptr || StringUtility::getInstance() == nullptr || this->m_spData.get() == nullptr || this->m_spData->find(this->m_kNumberStringKey) == this->m_spData->end() || this->m_spPipeline.get() == nullptr || this->m_spPipeline->getManager() == nullptr || (pChooseLangPipeline = dynamic_cast<PSChooseLanguage *>(this->m_spPipeline->getStateByKey(PIPELINE_STATE_TYPE_CHOOSE_LANG))) == nullptr || this->m_iTryCount >= this->m_iMaxTries) {
        if(this->m_iTryCount >= this->m_iMaxTries)
            throw InputException(INPUT_EXCEPTION_REASON_EXCEED_TRY_COUNT);

        this->m_eNextState = PIPELINE_STATE_TYPE_FINISH;
		
		return false;
	}

	pcNumberStringBuffer = new char[PS_INPUT_NUMBER_STRING_BUFFER_SIZE];

    wcout<<L"Input number string: ";

	if (StandardIOUtility::getInstance()->readLine(pcNumberStringBuffer, PS_INPUT_NUMBER_STRING_BUFFER_SIZE) == false) {
		this->m_eNextState = PIPELINE_STATE_TYPE_FINISH;
		this->m_iTryCount = 0;

		delete[] pcNumberStringBuffer;

		return false;
	}

    if (this->m_spData->find(pChooseLangPipeline->getLangKey()) == this->m_spData->end() || (pLang = dynamic_cast<StringData *>((*(this->m_spData.get()))[pChooseLangPipeline->getLangKey()].get())) == nullptr) {
		this->m_eNextState = PIPELINE_STATE_TYPE_FINISH;
		this->m_iTryCount = 0;

		delete[] pcNumberStringBuffer;

		return false;
	}

    spConfig.reset(new Config(pLang->getValue(), nullptr));

    c.setData(spConfig);

    spConfig.reset();

	if ((pConfig = dynamic_cast<Config *>(this->m_spPipeline->getManager()->get(c))) == nullptr) {
		this->m_eNextState = PIPELINE_STATE_TYPE_FINISH;
		this->m_iTryCount = 0;

		delete[] pcNumberStringBuffer;

		return false;
	}

	if (StringUtility::getInstance()->isAllDigitsValid(pcNumberStringBuffer, pConfig) == false) {
		this->m_eNextState = PIPELINE_STATE_TYPE_HELP;
		this->m_iTryCount++;

		delete[] pcNumberStringBuffer;

        return true;
	}

    wcout<<L"All the digits is valid"<<endl;

	this->m_spData->at(this->m_kNumberStringKey).reset(new StringData(pcNumberStringBuffer));

	this->m_iTryCount = 0;
	this->m_eNextState = PIPELINE_STATE_TYPE_HANDLE_NUMBER_STRING;

	delete[] pcNumberStringBuffer;

	wcout << L"Ending to parse number string" << endl;

	return true;
}

PipelineStateType PSInputNumberString::determineNextStateType() const {
	PSHelp *pHelpPipeline;

    if (this->m_eNextState == PIPELINE_STATE_TYPE_HELP && this->m_spPipeline.get() != nullptr && (pHelpPipeline = dynamic_cast<PSHelp *>(this->m_spPipeline->getStateByKey(PIPELINE_STATE_TYPE_HELP))) != nullptr)
		pHelpPipeline->setHelpType(PS_HELP_TYPE_NUMBER_STRING);

	return this->m_eNextState;
}

bool PSInputNumberString::cleanup() {
	StringData *pStringNumber;

	if (this->m_spData.get() == nullptr)
		return false;

	if (this->m_spData->find(this->m_kNumberStringKey) != this->m_spData->end() && (pStringNumber = dynamic_cast<StringData *>((*(this->m_spData.get()))[this->m_kNumberStringKey].get())) != nullptr)
		(*(this->m_spData.get()))[this->m_kNumberStringKey].reset();

	this->m_iTryCount = 0;

	return true;
}

Key PSInputNumberString::getNumberStringKey() {
	return this->m_kNumberStringKey;
}

int16_t PSInputNumberString::getMaxTries() {
	return this->m_iMaxTries;
}

void PSInputNumberString::setMaxTries(const int16_t iMaxTries) {
	if (iMaxTries <= 0)
		return;

	this->m_iMaxTries = iMaxTries;
}

int16_t PSInputNumberString::getTryCount() {
	return this->m_iTryCount;
}

void PSInputNumberString::setTryCount(const int16_t iTryCount) {
	if (iTryCount <= 0)
		return;

	this->m_iTryCount = iTryCount;
}

bool PSInputNumberString::constructPossibleStates() {
	if (this->m_upPossibleStates.get() == nullptr)
		return false;

	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_FINISH);
	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_HELP);
	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_HANDLE_NUMBER_STRING);

	return true;
}

bool PSInputNumberString::determineNumberStringKey() {
	PSChooseLanguage *pChooseLanguage;

	if (this->m_spPipeline.get() == nullptr || (pChooseLanguage = dynamic_cast<PSChooseLanguage *>(this->m_spPipeline->getStateByKey(PIPELINE_STATE_TYPE_CHOOSE_LANG))) == nullptr) {
		this->m_kNumberStringKey = -1;
		
		return false;
	}

	this->m_kNumberStringKey = pChooseLanguage->getLangKey() > 0 && pChooseLanguage->getLangKey() < LANGUAGE_MAX_VALUE - 1 ? pChooseLanguage->getLangKey() + 1 : pChooseLanguage->getLangKey() - 1;

	return true;
}
