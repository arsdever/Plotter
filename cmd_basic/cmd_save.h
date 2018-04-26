#ifndef CMD_SAVE_H
#define CMD_SAVE_H

#include "cmd_include.h"

class CCMDSave : public ICommand
{
public:
	// Constructor
	CCMDSave(ICommand *pParent = nullptr, std::string strIName = "save");
	// Destructor
	~CCMDSave() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

#endif