#include "cmd_delete.h"
#include "cmd_include.h"

CCMDDelete::CCMDDelete(ICommand *pParent, std::string strIName)
	:ICommand(pParent, strIName)
{
	SetCMD(this);

	Argument arg = GetArgument(true);

	if (arg == "graph")
		SetCMD(new CCMDDeleteGraph(this));
	else if (arg == "vertex")
		SetCMD(new CCMDDeleteVertex(this));
	else if (arg == "edge")
		SetCMD(new CCMDDeleteEdge(this));
	else if (arg == "help")
		SetCMD(new CCMDHelp(this));
	else if (arg == "")
		outputStream << "Error: Few arguments was passed" << std::endl;
	else
		outputStream << CString("Error: Invalid argument passed \"%\".").Arg(arg) << std::endl;
}

CResult CCMDDelete::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);

	return CResult::Fail;
}
