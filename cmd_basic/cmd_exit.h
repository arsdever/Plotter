#ifndef CMD_EXIT_H
#define CMD_EXIT_H

#include "cmd_include.h"

class CCMDExit : public ICommand
{
protected:
	// Exit code
	int m_nExitResult;

public:
	// Constructor
	CCMDExit(ICommand *pParent = nullptr, std::string strIName = "exit");
	// Destructor
	~CCMDExit() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
	// Set exit code
	inline CResult SetExitCode(int nExitCode) { m_nExitResult = nExitCode; return CResult::Success; }
	// Return exit code
	inline int Result() const { return m_nExitResult; }
};

#endif