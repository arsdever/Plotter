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

#include "cmd_load.h"
#include <fstream>

CCMDLoad::CCMDLoad(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);
}

CResult CCMDLoad::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);

	CString arg = GetArgument();

	if (arg == "")
	{
		outputStream << "Error: No input file" << std::endl;
		return CResult::Fail;
	}

	CGraph *pGraph = new CGraph();

	if (pGraph == nullptr)
	{
		outputStream << "Error: Cannot load graph." << std::endl;
		return CResult::Fail;
	}

	std::ifstream file;
	file.open(arg, std::fstream::in);
	if (!file.is_open())
	{
		outputStream << CString("Error: Cannot open input file \"%\"").Arg(arg) << std::endl;
		return CResult::Fail;
	}
	
	CResult resLoad;
	if (arg.GetExtention() == "xml")
		resLoad = pGraph->LoadXML(file);
	else
		resLoad = pGraph->Load(file);

	if (resLoad.Failure()) {
		if (resLoad.GetResult() & CResult::Already)
		{
			outputStream << CString("Warning: Graph name already exist") << std::endl;
			delete pGraph;
			return resLoad;
		}

		outputStream << "Error: Invalid file." << std::endl;
		delete pGraph;
		return resLoad;
	}

	outputStream << CString("Graph was successfully loaded from file \"./%\".\n New graph was created with name \"%\".").Arg(CGraph::GetGraphList().back()->GetName()).Arg(arg) << std::endl;
	return CResult::Success;
}