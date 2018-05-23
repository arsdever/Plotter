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

#ifndef ITYPE_H
#define ITYPE_H

#include <string>

#ifndef EXCEPT_PATH
#define EXCEPT_PATH "From file \"" + std::string(__FILE__) + "\": at line: " + std::to_string(__LINE__)
#define EXCEPT_PATH1 "File \"" + std::string(__FILE__) + "\": in function " + std::string(__func__) + " at line: " + std::to_string(__LINE__)
#endif

class CResult;
class CGraph;

class IType
{
private:
	std::string m_strInstanceName;

public:
	// Constructor
	IType(std::string const& strInstanceName = "unknown")
		:m_strInstanceName(strInstanceName)
	{}
	// Destructor
	virtual ~IType() {}

	// Sets instance vertex
	virtual CResult SetInstanceName(std::string const& strName);
	// Returns instance vertex
	virtual inline std::string GetInstanceName() const { return m_strInstanceName; }
};

#endif