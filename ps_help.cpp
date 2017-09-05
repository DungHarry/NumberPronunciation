/*
	Author: Dung Ly Viet
	Date created: September 5th, 2017
	Compiler: Visual C++ Compiler 2013

	Description: this is the source code file of the PSHelp class in C++ programming language
*/

#include "ps_help.h"

PSHelp::PSHelp() :
	PipelineState (),
	m_eNextState (PIPELINE_STATE_FINISH),
	m_eHelpType (PS_HELP_TYPE_NONE)
{
	this->m_eStateType = PIPELINE_STATE_TYPE_HELP;
}

PSHelp::PSHelp(PSHelpType eHelpType, Pipeline *pPipeline, map<Key, shared_ptr<Base>> *pData) :
	PipelineState (pPipeline, pData, PIPELINE_STATE_TYPE_HELP),
	m_eNextState (PIPELINE_STATE_FINISH),
	m_eHelpType (eHelpType < PS_HELP_TYPE_NONE || eHelpType >= PS_HELP_TYPE_COUNT ? PS_HELP_TYPE_NONE : eHelpType)
{

}

PSHelp::~PSHelp() {

}

bool PSHelp::execute() {
	if (this->m_eHelpType <= PS_HELP_TYPE_NONE || this->m_eHelpType >= PS_HELP_TYPE_COUNT) {
		this->m_eNextState = PIPELINE_STATE_FINISH;
		
		return false;
	}

	if (this->m_eHelpType == PS_HELP_TYPE_LANG) {
		this->displayHelpLang();

		this->m_eNextState = PIPELINE_STATE_TYPE_CHOOSE_LANG;
	} else if (this->m_eHelpType == PS_HELP_TYPE_NUMBER_STRING) {
		this->displayHelpNumberString();

		this->m_eNextState = PIPELINE_STATE_TYPE_INPUT_NUMBER_STRING;
	} else 
		this->m_eNextState = PIPELINE_STATE_FINISH;

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

	this->m_upPossibleStates->insert(PIPELINE_STATE_FINISH);
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
				cout << ", " << endl;

			cout << pConfig->getLang()->getName() << " ";
		}

	wcout << endl;
}

void PSHelp::displayHelpNumberString() {
	Config *pConfig;

	if (this->m_eHelpType != PS_HELP_TYPE_NUMBER_STRING)
		return;

	wcout << "The valid characters: ";
}