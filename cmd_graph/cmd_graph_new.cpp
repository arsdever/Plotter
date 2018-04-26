#include "cmd_graph_new.h"

CCMDNewVertex::CCMDNewVertex(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);
}

CResult CCMDNewVertex::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);


	CGraph *pGraph = dynamic_cast<CGraph *>(pObject);

	if (pGraph == nullptr)
	{
		outputStream << "Error: No graph selected." << std::endl;
		return CResult::Fail;
	}

	Argument arg;
	int nFailureCount = 0;
	std::list<std::string> strFailList;

	if (GetArgumentList()->size() > 1)
	{
		while (GetArgumentList()->size() > 0)
		{
			arg = GetArgument();
			CVertex *pVertex = new CVertex(arg);

			if (pVertex == nullptr || ((pGraph->AddVertex(pVertex).GetResult() & CResult::Already) == CResult::Already))
			{
				++nFailureCount;
				strFailList.push_back(arg);
			}
		}

		if (nFailureCount == 0)
		{
			outputStream << "All vertices was created successfully." << std::endl;
			return CResult::Success;
		}

		outputStream << CString("Error: Filed to create % vertices.").Arg(std::to_string(nFailureCount)) << std::endl;

		for (auto it : strFailList)
		{
			outputStream << '\t' << it << std::endl;
		}

		return CResult::Fail;
	}

	arg = GetArgument();
	int argToInt = -1;
	bool bPassedNumber = true;

	try
	{
		argToInt = stoi(arg);
	}
	catch (...)
	{
		bPassedNumber = false;
	}

	if (bPassedNumber)
	{
		outputStream << CString("Generating % vertices...").Arg(std::to_string(argToInt)) << std::endl;

		if (argToInt <= 0)
		{
			outputStream << "Error: Invalid number of  vertices." << std::endl;
			return CResult::Fail;
		}

		CResult result = CResult::Success;
		int i = 0;

		for (; i < argToInt; ++i)
		{
			Argument vertexName = pGraph->GetDefaultVertexName();
			CVertex *pVertex = new CVertex(vertexName);

			if (pVertex == nullptr)
			{
				result = CResult::Fail;
				break;
			}

			result = pGraph->AddVertex(pVertex);

			if (result.Failure())
				break;
		}

		if (result.Failure())
		{
			outputStream << CString("Error: Error while generating vertices. Generated % vertices. Had to generate  %.").Arg(std::to_string(argToInt)).Arg(std::to_string(i)) << std::endl;
			return result;
		}

		outputStream << "Well done." << std::endl;
		return result;
	}

	if (arg == "")
	{
		arg = pGraph->GetDefaultVertexName();
		outputStream << "Warning: No name passed. Default name will be generated." << std::endl;
	}

	CVertex *pVertex = new CVertex(arg);
	CResult result = pGraph->AddVertex(pVertex);
	if (result.Failure() || (result.GetResult() & CResult::Already))
	{
		delete pVertex;
		outputStream << "Warning: Vertex already exist." << std::endl;
		return result;
	}

	outputStream << CString("New vertex was created by name \"%\" and was added to graph \"%\".").Arg(pGraph->GetName()).Arg(arg);

	return CResult::Success;
}

CCMDNewEdge::CCMDNewEdge(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);
}

CResult CCMDNewEdge::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);


	CGraph *pGraph = dynamic_cast<CGraph *>(pObject);

	if (pGraph == nullptr)
	{
		outputStream << "Error: No graph selected." << std::endl;
		return CResult::Fail;
	}

	if (GetArgumentList()->size() < 2)
	{
		outputStream << "Error: Few arguments was passed" << std::endl;
		return CResult::Fail;
	}

	CVertex *pVertex1 = pGraph->GetVertex(GetArgument());
	CVertex *pVertex2 = pGraph->GetVertex(GetArgument());

	if (pVertex1 == nullptr || pVertex2 == nullptr)
	{
		outputStream << "Error: Wrong vertex name passed." << std::endl;
		return CResult::Fail;
	}

	Argument arg = GetArgument();

	if (arg == "")
	{
		arg = pGraph->GetDefaultEdgeName();
		outputStream << "Warning: No edge name passed. Default edge name will be generated." << std::endl;
	}

	CEdge *pEdge = new CEdge(arg, pVertex1, pVertex2);
	CResult result = pGraph->AddEdge(pEdge);

	if (result.Failure() || (result.GetResult() & CResult::Already))
	{
		outputStream << CString("Error: Cannot create edge by name \"%\".").Arg(arg) << std::endl;
		delete pEdge;
		return result;
	}

	outputStream << CString("New vertex was created by name \"%\" and was added to graph \"%\".").Arg(pGraph->GetName()).Arg(arg) << std::endl;

	return CResult::Success;
}

CCMDNewGraph::CCMDNewGraph(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);
}

CResult CCMDNewGraph::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);

	Argument arg = GetArgument();

	if (arg == "")
	{
		arg = CGraph::GetDefaultGraphName();
		outputStream << "Warning: No name passed. Default name will be generated." << std::endl;
	}
	else
	{
		if (CGraph::IsExist(arg))
		{
			outputStream << CString("Warning: Graph name \"%\" already exist.").Arg(arg) << std::endl;
			return CResult::EResultType(CResult::Fail | CResult::Already);
		}
	}

	pObject = new CGraph(arg);

	if (pObject == nullptr)
	{
		outputStream << CString("Error: Cannot create graph by name \"%\".").Arg(arg) << std::endl;
		return CResult::Fail;
	}

	outputStream << CString("New graph was created by name \"%\" and was set selected.").Arg(arg) << std::endl;

	return CResult::Success;
}

CCMDNewXEdge::CCMDNewXEdge(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);
}

CResult CCMDNewXEdge::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);


	CGraph *pGraph = dynamic_cast<CGraph *>(pObject);

	if (pGraph == nullptr)
	{
		outputStream << "Error: No graph selected." << std::endl;
		return CResult::Fail;
	}

	if (GetArgumentList()->size() < 2)
	{
		outputStream << "Error: Few arguments was passed" << std::endl;
		return CResult::Fail;
	}

	CVertex *pVertex1 = pGraph->GetVertex(GetArgument());
	CVertex *pVertex2 = pGraph->GetVertex(GetArgument());

	if (pVertex1 == nullptr || pVertex2 == nullptr)
	{
		outputStream << "Error: Wrong vertex name passed." << std::endl;
		return CResult::Fail;
	}

	Argument arg = GetArgument();

	if (arg == "")
	{
		arg = pGraph->GetDefaultEdgeName();
		outputStream << "Warning: No edge name passed. Default edge name will be generated." << std::endl;
	}

	CXEdge *pEdge = new CXEdge(arg, pVertex1, pVertex2);
	CResult result = pGraph->AddXEdge(pEdge);

	if (result.Failure() || (result.GetResult() & CResult::Already))
	{
		outputStream << CString("Error: Cannot create edge by name \"%\".").Arg(arg) << std::endl;
		delete pEdge;
		return result;
	}

	outputStream << CString("New vertex was created by name \"%\" and was added to graph \"%\".").Arg(pGraph->GetName()).Arg(arg) << std::endl;

	return CResult::Success;
}