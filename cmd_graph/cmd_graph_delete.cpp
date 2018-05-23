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

#include "cmd_graph_delete.h"

CCMDDeleteVertex::CCMDDeleteVertex(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);
}

CResult CCMDDeleteVertex::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);

	CGraph *pGraph = dynamic_cast<CGraph *>(pObject);

	if (pGraph == nullptr)
	{
		outputStream << "Error: No graph selected." << std::endl;
		return CResult::EResultType(CResult::Fail | CResult::Cast);
	}

	Argument arg = GetArgument();

	if (arg == "")
	{
		outputStream << "Error: Vertex name not specified." << std::endl;
		return CResult::Fail;
	}

	CVertex *pVertex = pGraph->GetVertex(arg);

	if (pVertex == nullptr)
	{
		outputStream << "Error: Vertex not found." << std::endl;
		return CResult::Fail;
	}

	return pGraph->RemoveVertex(pVertex);
}

CCMDDeleteGraph::CCMDDeleteGraph(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);
}

CResult CCMDDeleteGraph::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);

	CGraph *pGraph = dynamic_cast<CGraph *>(pObject);
	Argument arg = GetArgument();

	if (arg != "")
	{
		pGraph = CGraph::GetGraphByName(arg);
	}

	if (pGraph == nullptr)
	{
		outputStream << "Error: Cannot allocate graph." << std::endl;
		return CResult::Fail;
	}

	delete pGraph;
	pObject = nullptr;

	return CResult::Success;
}

CCMDDeleteEdge::CCMDDeleteEdge(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);
}

CResult CCMDDeleteEdge::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);

	CGraph *pGraph = dynamic_cast<CGraph *>(pObject);

	if (pGraph == nullptr)
	{
		outputStream << "Error: No graph selected." << std::endl;
		return CResult::EResultType(CResult::Fail | CResult::Cast);
	}

	Argument arg = GetArgument();
	Argument arg1 = GetArgument();

	if (arg == "")
	{
		outputStream << "Error: Edge name not specified." << std::endl;
		return CResult::Fail;
	}

	CEdge *pEdge = nullptr;

	if (arg1 == "")
		pEdge = pGraph->GetEdge(arg);
	else
		pEdge = pGraph->GetEdge(arg, arg1);

	if (pEdge == nullptr)
	{
		outputStream << "Error: Edge not found." << std::endl;
		return CResult::Fail;
	}

	return pGraph->RemoveEdge(pEdge);
}