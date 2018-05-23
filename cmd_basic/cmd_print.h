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

#ifndef CMD_PRINT_H
#define CMD_PRINT_H

#include "cmd_include.h"

class CCMDPrint : public ICommand
{
public:
	// Constructor
	CCMDPrint(ICommand *pParent = nullptr, std::string strIName = "print");
	// Destructor
	~CCMDPrint() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

#endif