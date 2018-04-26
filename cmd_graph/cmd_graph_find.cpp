#include "cmd_graph_find.h"

CCMDFindVertex::CCMDFindVertex(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);
}

CResult CCMDFindVertex::Execute(IType *& pObject)
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
		outputStream << "Error: Few arguments was passed" << std::endl;
		return CResult::Fail;
	}

	CVertex *pVertex = pGraph->FindVertex(arg);

	if (pVertex == nullptr)
	{
		outputStream << CString("Vertex by name \"%\" does not belong to selected graph.").Arg(arg) << std::endl;
		return CResult::Fail;
	}

	outputStream << CString("Vertex by name \"%\" belongs to selected graph.").Arg(arg) << std::endl;

	return CResult::Success;
}

CCMDFindEdge::CCMDFindEdge(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);
}

CResult CCMDFindEdge::Execute(IType *& pObject)
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
		outputStream << "Error: Few arguments was passed" << std::endl;
		return CResult::Fail;
	}

	CEdge *pEdge = pGraph->FindEdge(arg);

	if (pEdge == nullptr)
	{
		outputStream << CString("Edge by name \"%\" does not belong to selected graph.").Arg(arg) << std::endl;
		return CResult::Fail;
	}

	outputStream << CString("Edge by name \"%\" belongs to selected graph.").Arg(arg) << std::endl;
	return CResult::Success;

	return CResult::Success;
}

CCMDFindGraph::CCMDFindGraph(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);
}

CResult CCMDFindGraph::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);

	Argument arg = GetArgument();

	if (arg == "")
	{
		outputStream << "Error: Few arguments was passed" << std::endl;
		return CResult::Fail;
	}

	CGraph *pGraph = CGraph::FindGraph(arg);

	if (pGraph == nullptr)
	{
		outputStream << CString("Graph by name \"%\" does not exist.").Arg(arg);
		return CResult::Fail;
	}

	outputStream << CString("Graph by name \"%\" exist.").Arg(arg);

	return CResult::Success;
}

CCMDFindPath::CCMDFindPath(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);
}

CResult CCMDFindPath::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);

	if (GetArgumentList()->size() < 2)
	{
		outputStream << "Error: Invalid count of vertices passed." << std::endl;
		return CResult::Fail;
	}

	Argument begin = GetArgument();
	Argument end = GetArgument();

	CGraph *pGraph = dynamic_cast<CGraph *>(pObject);

	if (pGraph == nullptr)
	{
		outputStream << "Error: No graph selected." << std::endl;
		return CResult::Fail;
	}

	CVertex *pVertex1 = pGraph->FindVertex(begin);
	CVertex *pVertex2 = pGraph->FindVertex(end);

	if (pVertex1 == nullptr)
	{
		outputStream << CString("Error: Vertex \"%\" does not belong to selected graph").Arg(begin) << std::endl;
		return CResult::Fail;
	}

	if (pVertex2 == nullptr)
	{
		outputStream << CString("Error: Vertex \"%\" does not belong to selected graph").Arg(end) << std::endl;
		return CResult::Fail;
	}

	CWrappedVertexList *pWrappers = new CWrappedVertexList(pGraph->GetVertexList());
	CVertexList *pPath = pGraph->FindPath(pWrappers, pVertex1, pVertex2, 0);

	if (pPath == nullptr)
	{
		outputStream << "Path not found." << std::endl;

		delete pWrappers;
		return CResult::Fail;
	}
	delete pWrappers;
	outputStream << CString("Path found.%").Arg(pPath->ToString());

	return CResult::Success;
}

CCMDFindSPath::CCMDFindSPath(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);
}

CResult CCMDFindSPath::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);

	if (GetArgumentList()->size() < 2)
	{
		outputStream << "Error: Invalid count of vertices passed." << std::endl;
		return CResult::Fail;
	}

	Argument begin = GetArgument();
	Argument end = GetArgument();

	CGraph *pGraph = dynamic_cast<CGraph *>(pObject);

	if (pGraph == nullptr)
	{
		outputStream << "Error: No graph selected." << std::endl;
		return CResult::Fail;
	}

	CVertex *pVertex1 = pGraph->FindVertex(begin);
	CVertex *pVertex2 = pGraph->FindVertex(end);

	if (pVertex1 == nullptr)
	{
		outputStream << CString("Error: Vertex \"%\" does not belong to selected graph").Arg(begin) << std::endl;
		return CResult::Fail;
	}

	if (pVertex2 == nullptr)
	{
		outputStream << CString("Error: Vertex \"%\" does not belong to selected graph").Arg(end) << std::endl;
		return CResult::Fail;
	}

	CWrappedVertexList *pWrappers = new CWrappedVertexList(pGraph->GetVertexList());
	CVertexList *pPath = pGraph->FindSPath(pWrappers, pVertex1, pVertex2, 0);

	if (pPath == nullptr)
	{
		outputStream << "Path not found." << std::endl;

		delete pWrappers;
		return CResult::Fail;
	}

	delete pWrappers;
	outputStream << CString("Path found.%").Arg(pPath->ToString()) << std::endl;

	return CResult::Success;
}