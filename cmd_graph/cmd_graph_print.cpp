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

#include "cmd_graph_print.h"

CCMDPrintName::CCMDPrintName(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);
}

CResult CCMDPrintName::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);

	CGraph *pGraph = dynamic_cast<CGraph *>(pObject);

	if (pGraph == nullptr)
	{
		outputStream << "Error: No graph selected" << std::endl;
		return CResult::Fail;
	}

	outputStream << "Current graph name: " << pGraph->GetName() << std::endl;

	return CResult::Success;
}

CCMDPrintNameList::CCMDPrintNameList(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);
}

CResult CCMDPrintNameList::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);

	GraphPtrList lst = CGraph::GetGraphList();
	outputStream << "Printing existing graph list:" << std::endl;
	int i = 1;

	for (GraphPtrList::const_iterator it = lst.cbegin(); it != lst.cend(); ++it)
	{
		outputStream << "  " << (((*it) == pObject) ? '>' : ' ') << ' ' << i << ": " << (*it)->GetName() << std::endl;
		++i;
	}

	return CResult::Success;
}

CCMDPrintGraph::CCMDPrintGraph(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);
}

CResult CCMDPrintGraph::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);

	CGraph *pGraph = dynamic_cast<CGraph *>(pObject);
	Argument arg = GetArgument();

	if (arg != "")
	{
		pGraph = CGraph::GetGraphByName(arg);

		if (pGraph == nullptr)
		{
			outputStream << CString("Error: No graph found by name \"%\"").Arg(arg) << std::endl;
			return CResult::Fail;
		}
	}

	if (pGraph == nullptr)
	{
		outputStream << "Error: Graph not set." << std::endl;
		return CResult::Fail;
	}

	outputStream << pGraph->ToString() << std::endl;
	return CResult::Success;
}