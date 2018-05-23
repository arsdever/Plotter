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