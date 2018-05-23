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

#ifndef CMD_GRAPH_DELETE
#define CMD_GRAPH_DELETE

#include "cmd_include.h"

class CCMDDeleteGraph : public ICommand
{
public:
	// Constructor
	CCMDDeleteGraph(ICommand *pParent = nullptr, std::string strIName = "delete graph");
	// Destructor
	~CCMDDeleteGraph() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

class CCMDDeleteVertex : public ICommand
{
public:
	// Constructor
	CCMDDeleteVertex(ICommand *pParent = nullptr, std::string strIName = "delete vertex");
	// Destructor
	~CCMDDeleteVertex() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

class CCMDDeleteEdge : public ICommand
{
public:
	// Constructor
	CCMDDeleteEdge(ICommand *pParent = nullptr, std::string strIName = "delete edge");
	// Destructor
	~CCMDDeleteEdge() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

#endif