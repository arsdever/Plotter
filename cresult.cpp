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

#include "cresult.h"

CResult::CResult(EResultType eType)
	: IType("result")
	, m_eType(eType)
{}


CResult::~CResult()
{}
