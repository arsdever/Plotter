#ifndef CMD_LOAD_H
#define CMD_LOAD_H

#include "cmd_include.h"

class CCMDLoad : public ICommand
{
public:
	// Constructor
	CCMDLoad(ICommand *pParent = nullptr, std::string strIName = "save");
	// Destructor
	~CCMDLoad() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

#endif