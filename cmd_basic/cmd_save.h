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

#ifndef CMD_SAVE_H
#define CMD_SAVE_H

#include "cmd_include.h"

class CCMDSave : public ICommand
{
public:
	// Constructor
	CCMDSave(ICommand *pParent = nullptr, std::string strIName = "save");
	// Destructor
	~CCMDSave() = default;
	// Execute CMD
	CResult Execute(IType *& pObject) override;
};

#endif