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

#ifndef CXMLTREE_H
#define CXMLTREE_H

#include "cstring.h"
#include "ctree.h"
#include <map>
#include <list>

class CXMLTree;
class CXMLData;

typedef std::map<CString, CString> Attributes;
typedef std::list<CXMLTree *> Subtrees;

class CXMLData final
{
public:
	CXMLData(CString strData);

public:
	bool operator == (CXMLData const& pValue);

private:
	Attributes m_mAttributes;
	CString m_strTagName;

	friend class CXMLTree;
};

class CXMLTree : public CTree<CXMLData>
{
public:
	CXMLTree(CStringList strList, CXMLTree *pParent = nullptr);
	CXMLTree(CString strName, CXMLTree *pParent = nullptr);
	virtual ~CXMLTree();
	
	inline CString GetName() const { return GetValueRef().m_strTagName.ToLower(); }
	inline Attributes GetAttributes() const { return GetValueRef().m_mAttributes; }
	CString GetAttribute(CString const& strKey) const;

public:
	static CXMLTree* Parse(std::istream &stream);
	static CString GetTag(std::istream &stream);
};

#endif