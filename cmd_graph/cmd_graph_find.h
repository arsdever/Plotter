/********************************************************************************/
/*																				*/
/*  This file is part of source codes of program Graph.							*/
/*  Program was developed as an course work of subject "Graph theory".			*/
/*																				*/
/*	Contacts:																	*/
/*		E-mail:	arsen.gharagyozyn.96@gmail.com									*/
/*		Phone:	+374 77 006 861													*/
/*																				*/
/*  Copyright Arsen Gharagyozyan © 2018 Armenia, Yerevan						*/
/*																				*/
/********************************************************************************/

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