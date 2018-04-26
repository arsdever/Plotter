#include "ccommand.h"
#include "cmd_include.h"
#include <sstream>

// Begin interface implementation -------------------------------------------------------------------------------------/

ICommand::~ICommand()
{
	SetCMD(GetParent());
}

CResult ICommand::SetParent(ICommand *pCMDptr)
{
	m_pParent = pCMDptr;
	return CResult::Success;
}
CResult ICommand::SetCMD(ICommand *pCMDptr)
{
	if(m_pCMD == pCMDptr)
		return CResult::EResultType(CResult::Success | CResult::Already);

	m_pCMD = pCMDptr;
	return CResult::Success;
}
CResult ICommand::SetCMDByName(std::string const& strName)
{
	SetCMD(ConstructCommand(strName));

	if (GetCMD() == nullptr)
	{
		ClearArguments();
		outputStream << CString("Error: Unknown command \"%\".").Arg(strName) << std::endl;
		return CResult::Fail;
	}
	
	return CResult::Success;
}
CResult ICommand::AppendArgument(Argument const& strArgument)
{
	try
	{
		m_slArguments->push(strArgument);
	}
	catch (...)
	{
		return CResult::Fail;
	}

	return CResult::Success;
}
inline Argument ICommand::GetArgument(bool bLowCase)
{
	if (m_slArguments->empty())
		return "";

	Argument t = m_slArguments->front();
	RemoveArgument();
	return bLowCase ? toLower(t) : t;
}
CResult ICommand::RemoveArgument()
{
	try
	{
		m_slArguments->pop();
	}
	catch (...)
	{
		return CResult::Fail;
	}

	return CResult::Success;
}
void ICommand::ClearArguments()
{
	while (GetArgument() != "");
}
CResult ICommand::Parse()
{
	std::string strCMDName;
	inputStream >> strCMDName;
	std::string strArg;
	char ch = 0;
	inputStream.get(ch);

	while (ch != '\n' && ch != 0)
	{
		inputStream.putback(ch);
		inputStream >> strArg;
		AppendArgument(strArg);
		inputStream.get(ch);
	}

	return SetCMDByName(toLower(strCMDName));
}
CResult ICommand::Execute(IType *& pObject)
{
	if (GetCMD() == this)
		return CResult::Success;

	return GetCMD()->Execute(pObject);
}

// Static members -----------------------------------------------------------------------------------------------------/

ICommand* ICommand::ConstructCommand(std::string const& strName)
{
		if (strName == "new")
			return new CCMDNew(this);
		if (strName == "find")
			return new CCMDFind(this);
		if (strName == "delete")
			return new CCMDDelete(this);
		if (strName == "set")
			return new CCMDSet(this);
		if (strName == "save")
			return new CCMDSave(this);
		if (strName == "load")
			return new CCMDLoad(this);
		if (strName == "print")
			return new CCMDPrint(this);
		if (strName == "help")
			return new CCMDHelp(this);
		if (strName == "exit")
			return new CCMDExit(this);

	return nullptr;
}

// End interface implementation ---------------------------------------------------------------------------------------/