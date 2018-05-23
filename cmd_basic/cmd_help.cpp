/********************************************************************************/
/*																				*/
/*  This file is part of source codes of program Graph.							*/
/*  Program was developed as an course work of subject "Graph theory".			*/
/*																				*/
/*	Contacts:																	*/
/*		E-mail:	arsen.gharagyozyn.96@gmail.com									*/
/*		Phone:	+374 77 006 861													*/
/*																				*/
/*  Copyright Arsen Gharagyozyan © 2018 Armenia, Yerevan						*/
/*																				*/
/********************************************************************************/

#include "cmd_help.h"

CCMDHelp::CCMDHelp(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);
	SetHelpAssistant(&g_ha_CMD);

	Argument arg = GetArgument(true);

	if (arg == "new")
		SetHelpAssistant(&g_ha_CMDNew);
	else if (arg == "find")
		SetHelpAssistant(&g_ha_CMDFind);
	else if (arg == "print")
		SetHelpAssistant(&g_ha_CMDPrint);
	else if (arg == "help")
		SetHelpAssistant(&g_ha_CMDHelp);
	else if (arg == "")
		;
	else
		outputStream << CString("Error: Invalid argument passed \"%\".").Arg(arg) << std::endl;
}

CResult CCMDHelp::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);

	outputStream << "Available commands are:" << std::endl;
	for (std::pair<std::string, std::string> it : (*GetHelpAssistant()))
	{
		outputStream << CString("\t% - %").Arg(it.second).Arg(it.first) << std::endl;
	}

	return CResult::Success;
}
