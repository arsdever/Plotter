#ifndef CMD_NEW_H
#define CMD_NEW_H

#include "cmd_include.h"

class CCMDNew : public ICommand
{
public:
	// Constructor
	CCMDNew(ICommand *pParent = nullptr, std::string strIName = "new");
	// Destructor
	~CCMDNew() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

#endif