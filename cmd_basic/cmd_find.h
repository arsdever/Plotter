#ifndef CMD_FIND_H
#define CMD_FIND_H

#include "cmd_include.h"

class CCMDFind : public ICommand
{
public:
	// Constructor
	CCMDFind(ICommand *pParent = nullptr, std::string strIName = "find");
	// Destructor
	~CCMDFind() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

#endif