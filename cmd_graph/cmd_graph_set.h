#ifndef CMD_GRAPH_SET
#define CMD_GRAPH_SET

#include "cmd_include.h"

class CCMDSet : public ICommand
{
public:
	// Constructor
	CCMDSet(ICommand *pParent = nullptr, std::string strIName = "set");
	// Destructor
	~CCMDSet() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

#endif