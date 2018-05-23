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

#ifndef CMD_LOAD_H
#define CMD_LOAD_H

#include "cmd_include.h"

class CCMDLoad : public ICommand
{
public:
	// Constructor
	CCMDLoad(ICommand *pParent = nullptr, std::string strIName = "save");
	// Destructor
	~CCMDLoad() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

#endif