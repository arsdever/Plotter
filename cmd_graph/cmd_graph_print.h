#ifndef CMD_GRAPH_PRINT
#define CMD_GRAPH_PRINT

#include "cmd_include.h"

class CCMDPrintName : public ICommand
{
public:
	// Constructor
	CCMDPrintName(ICommand *pParent = nullptr, std::string strIName = "print graph vertex");
	// Destructor
	~CCMDPrintName() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

class CCMDPrintNameList : public ICommand
{
public:
	// Constructor
	CCMDPrintNameList(ICommand *pParent = nullptr, std::string strIName = "print list of graphs");
	// Destructor
	~CCMDPrintNameList() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

class CCMDPrintGraph : public ICommand
{
public:
	// Constructor
	CCMDPrintGraph(ICommand *pParent = nullptr, std::string strIName = "print graph");
	// Destructor
	~CCMDPrintGraph() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

#endif