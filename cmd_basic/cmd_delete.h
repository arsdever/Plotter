#ifndef CMD_DELETE_H
#define CMD_DELETE_H

#include "cmd_include.h"

class CCMDDelete : public ICommand
{
public:
	// Constructor
	CCMDDelete(ICommand *pParent = nullptr, std::string strIName = "delete");
	// Destructor
	~CCMDDelete() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

#endif