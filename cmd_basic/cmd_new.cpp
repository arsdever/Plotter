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

#include "cmd_new.h"

CCMDNew::CCMDNew(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);

	Argument arg = GetArgument(true);

	if (arg == "graph")
		SetCMD(new CCMDNewGraph(this));
	else if (arg == "edge")
		SetCMD(new CCMDNewEdge(this));
	else if (arg == "xedge")
		SetCMD(new CCMDNewXEdge(this));
	else if (arg == "vertex")
		SetCMD(new CCMDNewVertex(this));
	else if (arg == "")
		outputStream << "Error: Few arguments was passed" << std::endl;
	else
		outputStream << CString("Error: Invalid argument passed \"%\".").Arg(arg);
}

CResult CCMDNew::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);

	return CResult::Fail;
}