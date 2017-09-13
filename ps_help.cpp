/*
	Author: Dung Ly Viet
	Date created: September 5th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the PSHelp class in C++ programming language
*/

#include "ps_help.h"

PSHelp::PSHelp() :
	PipelineState (),
	m_eNextState (PIPELINE_STATE_TYPE_FINISH),
	m_eHelpType (PS_HELP_TYPE_NONE)
{
	this->m_eStateType = PIPELINE_STATE_TYPE_HELP;

    this->constructPossibleStates();
}

PSHelp::PSHelp(PSHelpType eHelpType, shared_ptr<Pipeline> pipeline, shared_ptr<map<Key, shared_ptr<Base>>> data) :
	PipelineState (pipeline, data, PIPELINE_STATE_TYPE_HELP),
	m_eNextState (PIPELINE_STATE_TYPE_FINISH),
	m_eHelpType (eHelpType < PS_HELP_TYPE_NONE || eHelpType >= PS_HELP_TYPE_COUNT ? PS_HELP_TYPE_NONE : eHelpType)
{
    this->constructPossibleStates();
}

PSHelp::~PSHelp() {

}

bool PSHelp::execute() {
	if (this->m_eHelpType <= PS_HELP_TYPE_NONE || this->m_eHelpType >= PS_HELP_TYPE_COUNT) {
		this->m_eNextState = PIPELINE_STATE_TYPE_FINISH;
		
		return false;
	}

	if (this->m_eHelpType == PS_HELP_TYPE_LANG) {
		this->displayHelpLang();

		this->m_eNextState = PIPELINE_STATE_TYPE_CHOOSE_LANG;
	} else if (this->m_eHelpType == PS_HELP_TYPE_NUMBER_STRING) {
		this->displayHelpNumberString();

		this->m_eNextState = PIPELINE_STATE_TYPE_INPUT_NUMBER_STRING;
	} else 
		this->m_eNextState = PIPELINE_STATE_TYPE_FINISH;

	return true;
}

PipelineStateType PSHelp::determineNextStateType() const {
	return this->m_eNextState;
}

bool PSHelp::cleanup() {

}

PSHelpType PSHelp::getHelpType() {
	return this->m_eHelpType;
}

void PSHelp::setHelpType(const PSHelpType eHelpType) {
	if (this->m_eHelpType < PS_HELP_TYPE_NONE || this->m_eHelpType >= PS_HELP_TYPE_COUNT)
		return;

	this->m_eHelpType = eHelpType;
}

bool PSHelp::constructPossibleStates() {
	if (this->m_upPossibleStates.get() == nullptr)
		return false;

	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_FINISH);
	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_CHOOSE_LANG);
	this->m_upPossibleStates->insert(PIPELINE_STATE_TYPE_INPUT_NUMBER_STRING);

	return true;
}

void PSHelp::displayHelpLang() {
	Config *pConfig;
	set<Container> *pSetConfigs;
	set<Container>::iterator iter;

	if (this->m_eHelpType != PS_HELP_TYPE_LANG || this->m_spPipeline.get() == nullptr || this->m_spPipeline->getManager() == nullptr || (pSetConfigs = this->m_spPipeline->getManager()->getObjects()) == nullptr)
		return;

	wcout << L"The available languages: ";

	for (iter = pSetConfigs->begin(); iter != pSetConfigs->end(); ++ iter)
		if ((pConfig = dynamic_cast<Config *>(iter->getData().get())) != nullptr) {
			if (iter != pSetConfigs->begin())
                wcout << L", ";

            wcout << pConfig->getLang()->getName();
		}

	wcout << endl;
}

void PSHelp::displayHelpNumberString() {
	PSChooseLanguage *pChooseLangPipelineState;
	StringData *pLang;
	Config *pConfig;
	Container c;
    shared_ptr<Comparable> spConfig (nullptr);
	NormalDigitAttribute *pNormalDigitAttribute;
	SpecialDigitAttribute *pSpecialDigitAttribute;
	set<Container> *pSet;
	set<Container>::iterator iter;

	if (this->m_eHelpType != PS_HELP_TYPE_NUMBER_STRING || this->m_spData.get() == nullptr || this->m_spPipeline.get() == nullptr || (pChooseLangPipelineState = dynamic_cast<PSChooseLanguage *>(this->m_spPipeline->getStateByKey(static_cast<PipelineStateKey>(PIPELINE_STATE_TYPE_CHOOSE_LANG)))) == nullptr || (pLang = dynamic_cast<StringData *>((*(this->m_spData.get()))[pChooseLangPipelineState->getLangKey()].get())) == nullptr || this->m_spPipeline->getManager() == nullptr)
		return;

    spConfig.reset(new Config(pLang->getValue(), nullptr));

    c.setData(spConfig);

    spConfig.reset();

	if ((pConfig = dynamic_cast<Config *>(this->m_spPipeline->getManager()->get(c))) == nullptr)
		return;

    wcout << L"The valid characters: " << endl << endl;
    wcout << L"Normal digits: ";

	if ((pSet = pConfig->getNormalDigitAttributes()) != nullptr) {
		for (iter = pSet->begin(); iter != pSet->end(); ++iter) {
			if ((pNormalDigitAttribute = dynamic_cast<NormalDigitAttribute *>(iter->getData().get())) != nullptr)
                wcout << (pNormalDigitAttribute->getDigit());
		}
	}

    wcout << endl << L"Special digits: ";

	if ((pSet = pConfig->getSpecialDigitAttributes()) != nullptr) {
		for (iter = pSet->begin(); iter != pSet->end(); ++iter) {
			if ((pSpecialDigitAttribute = dynamic_cast<SpecialDigitAttribute *>(iter->getData().get())) != nullptr)
                wcout << (pSpecialDigitAttribute->getDigit());
		}
	}

	wcout << endl << endl << L"Note: the number must contain the digits above and it needs to be well formated as a number(integer, float)" << endl;
}
