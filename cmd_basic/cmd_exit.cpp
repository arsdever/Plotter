#include "cmd_exit.h"
#include "cmd_include.h"

CCMDExit::CCMDExit(ICommand *pParent, std::string strIName)
	: ICommand(pParent, strIName)
{
	SetCMD(this);

	if (GetArgument(true) == "help")
		SetCMD(new CCMDHelp(this));
}

CResult CCMDExit::Execute(IType *& pObject)
{
	if (GetCMD() != this)
		return GetCMD()->Execute(pObject);

	eFlags = Flags(eFlags | Exit);
	return CResult::Success;
}