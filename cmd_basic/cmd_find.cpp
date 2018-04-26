#include "cmd_find.h"

CCMDFind::CCMDFind(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);

	Argument arg = GetArgument(true);

	if (arg == "graph")
		SetCMD(new CCMDFindGraph(this));
	else if (arg == "edge")
		SetCMD(new CCMDFindEdge(this));
	else if (arg == "vertex")
		SetCMD(new CCMDFindVertex(this));
	else if (arg == "path")
		SetCMD(new CCMDFindPath(this));
	else if (arg == "spath")
		SetCMD(new CCMDFindSPath(this));
	else if (arg == "")
		outputStream << "Error: Few arguments was passed" << std::endl;
	else
		outputStream << CString("Error: Invalid argument passed \"%\".").Arg(arg) << std::endl;
}

CResult CCMDFind::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);

	return CResult::Success;
}
