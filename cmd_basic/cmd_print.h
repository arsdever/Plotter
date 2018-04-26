#ifndef CMD_PRINT_H
#define CMD_PRINT_H

#include "cmd_include.h"

class CCMDPrint : public ICommand
{
public:
	// Constructor
	CCMDPrint(ICommand *pParent = nullptr, std::string strIName = "print");
	// Destructor
	~CCMDPrint() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

#endif