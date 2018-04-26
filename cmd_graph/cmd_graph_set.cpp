#include "cmd_graph_set.h"

CCMDSet::CCMDSet(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);
}

CResult CCMDSet::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);

	Argument arg = GetArgument();

	if (arg == "")
	{
		outputStream << "Error: Graph name not specified." << std::endl;
		return CResult::Fail;
	}

	CGraph *pGraph(CGraph::GetGraphByName(arg));

	if (pGraph == nullptr)
	{
		outputStream << CString("Error: Cannot allocate graph by name \"%\".").Arg(arg) << std::endl;
		return CResult::Fail;
	}

	if (pGraph == pObject)
	{
		outputStream << "Warning: Graph was already selected." << std::endl;
		return CResult::Fail;
	}

	pObject = pGraph;

	return CResult::Success;
}