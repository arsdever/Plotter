#ifndef CMD_GRAPH_FIND
#define CMD_GRAPH_FIND

#include "cmd_include.h"

class CCMDFindGraph : public ICommand
{
public:
	// Constructor
	CCMDFindGraph(ICommand *pParent = nullptr, std::string strIName = "find graph");
	// Destructor
	~CCMDFindGraph() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

class CCMDFindVertex : public ICommand
{
public:
	// Constructor
	CCMDFindVertex(ICommand *pParent = nullptr, std::string strIName = "find vertex");
	// Destructor
	~CCMDFindVertex() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

class CCMDFindEdge : public ICommand
{
public:
	// Constructor
	CCMDFindEdge(ICommand *pParent = nullptr, std::string strIName = "find edge");
	// Destructor
	~CCMDFindEdge() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

class CCMDFindPath : public ICommand
{
public:
	// Constructor
	CCMDFindPath(ICommand *pParent = nullptr, std::string strIName = "find path");
	// Destructor
	~CCMDFindPath() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};
class CCMDFindSPath : public ICommand
{
public:
	// Constructor
	CCMDFindSPath(ICommand *pParent = nullptr, std::string strIName = "find path");
	// Destructor
	~CCMDFindSPath() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

#endif