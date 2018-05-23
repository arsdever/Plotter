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

#ifndef CMD_GRAPH_NEW
#define CMD_GRAPH_NEW

#include "cmd_include.h"

class CCMDNewGraph : public ICommand
{
public:
	// Constructor
	CCMDNewGraph(ICommand *pParent = nullptr, std::string strIName = "new graph");
	// Destructor
	~CCMDNewGraph() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

class CCMDNewVertex : public ICommand
{
public:
	// Constructor
	CCMDNewVertex(ICommand *pParent = nullptr, std::string strIName = "new vertex");
	// Destructor
	~CCMDNewVertex() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

class CCMDNewEdge : public ICommand
{
public:
	// Constructor
	CCMDNewEdge(ICommand *pParent = nullptr, std::string strIName = "new edge");
	// Destructor
	~CCMDNewEdge() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

class CCMDNewXEdge : public ICommand
{
public:
	// Constructor
	CCMDNewXEdge(ICommand *pParent = nullptr, std::string strIName = "new edge");
	// Destructor
	~CCMDNewXEdge() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

#endif