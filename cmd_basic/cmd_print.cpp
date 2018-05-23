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

#include "cmd_print.h"
#include "cmd_include.h"

CCMDPrint::CCMDPrint(ICommand *pParent, std::string strIName)
	: ICommand(pParent, strIName)
{
	SetCMD(this);

	Argument arg = GetArgument(true);

	if (arg == "name")
		SetCMD(new CCMDPrintName(this));
	else if (arg == "names")
		SetCMD(new CCMDPrintNameList(this));
	else if (arg == "graph")
		SetCMD(new CCMDPrintGraph(this));
	else if (arg == "")
		outputStream << "Error: Few arguments was passed" << std::endl;
	else
		outputStream << CString("Error: Invalid argument passed \"%\".").Arg(arg) << std::endl;
}

CResult CCMDPrint::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);

	return CResult::Fail;
}