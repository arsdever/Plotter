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

#ifndef CSTRING_H
#define CSTRING_H

#include <string>
#include <iostream>
#include <list>
#include "itype.h"

#define Operator(op) \
inline bool operator ##op (CString const& strString) const { return m_strCore ##op strString.m_strCore; } \
inline bool operator ##op (std::string const& strString) const { return m_strCore ##op strString; } \
inline bool operator ##op (const char *const strString) const { return m_strCore ##op std::string(strString); } \

class CStringList;

// String wrapper
class CString : public IType
{
public:
	// Constructor
	CString();
	// Constructor
	CString(const char *const strInit);
	// Constructor
	CString(char const& strInit);
	// Constructor
	CString(std::string strInit);
	// Copy constructor
	CString(CString const& strInit) = default;
	// Destructor
	virtual ~CString();

	// Swap '%' symbol with argument
	CString& Arg(CString const& strArgument);
	// Swap '%' symbol with argument
	CString Arg(CString const& strArgument) const;

	// Return equivalent string transfered to lowcase
	CString ToLower() const;
	// Return equivalent string transferet to uppercase
	CString ToUpper() const;
	// Return equivalent std string
	inline std::string ToStdString() const { return m_strCore; }

	// Split by symbol
	CStringList Split(char chSymbol = ' ') const;
	// Get extention of file
	inline CString GetExtention() const;

public:
	inline void push_back(char chSymbol);

	// Operators

	CString& operator += (CString const& strString);

	friend std::istream& operator >> (std::istream &stream, CString string);
	friend std::ostream& operator << (std::ostream &stream, CString const& string);

	friend CString operator + (CString const& strString1, CString const& strString2);
	friend CString operator + (std::string const& strString1, CString const& strString2);
	friend CString operator + (CString const& strString1, std::string const& strString2);
	friend CString operator + (char const& strString1, CString const& strString2);
	friend CString operator + (CString const& strString1, char const& strString2);

	inline CString& operator = (CString const& strString2) = default;
	inline CString& operator = (std::string const& strString2);
	inline CString& operator = (char const& strString2);

	Operator(==)
	Operator(!=)
	Operator(<)
	Operator(>)

	inline char operator [] (unsigned nIndex);

	// std::string cast
	operator std::string();

private:
	std::string m_strCore;

};

class CStringList : public std::list<CString>
{

};

#include "cstring_inline.h"

#endif