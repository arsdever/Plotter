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

#include "cmd_save.h"
#include "cmd_include.h"
#include <fstream>

CCMDSave::CCMDSave(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);
}

CResult CCMDSave::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);

	Argument arg = GetArgument();
	std::string strOutputFile = "";
	CGraph *pGraph = nullptr;

	if (arg == "" || GetArgumentList()->size() == 0)
	{
		strOutputFile = "output.grp";

		if(arg != "")
			strOutputFile = arg;

		pGraph = dynamic_cast<CGraph *>(pObject);
	}
	else
	{
		strOutputFile = arg;
		pGraph = CGraph::FindGraph(GetArgument());
	}
	
	if (pGraph == nullptr)
	{
		outputStream << "Error: No graph found." << std::endl;
		return CResult::Fail;
	}

	std::ofstream file;
	file.open(strOutputFile, std::fstream::in | std::fstream::out);
	if (file.is_open())
	{
		outputStream << CString("Warning: File with name \"%\" exist. Overwrite it?").Arg(strOutputFile) << std::endl;
		char ans = 0;
		while (ans != 'y' && ans != 'n')
		{
			outputStream << "\tAnswer y/n: ";
			inputStream >> ans;
			inputStream.clear();
		}
		if (ans == 'n')
		{
			outputStream << "Operation canceled." << std::endl;
			return CResult::Fail;
		}
	}
	else
	{
		file.open(strOutputFile, std::fstream::out);
		if (!file.is_open())
		{
			outputStream << CString("Error: Cannot open output file for writing - \"./%\"").Arg(strOutputFile) << std::endl;
			return CResult::Fail;
		}
	}
	file.close();
	file.open(strOutputFile, std::fstream::out);

	pGraph->Save(file);
	outputStream << "Graph was saved successfully to file \"./" << strOutputFile << "\"" << std::endl;

	return CResult::Success;
}