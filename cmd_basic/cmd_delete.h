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

#ifndef CMD_DELETE_H
#define CMD_DELETE_H

#include "cmd_include.h"

class CCMDDelete : public ICommand
{
public:
	// Constructor
	CCMDDelete(ICommand *pParent = nullptr, std::string strIName = "delete");
	// Destructor
	~CCMDDelete() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

#endif