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

#include "cxmltree.h"
#include "cexcept.h"
#include "cresult.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CXMLData
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CXMLData::CXMLData(CString strName)
	: m_strTagName(strName)
{
}

bool CXMLData::operator == (CXMLData const& pValue)
{
	return m_strTagName == pValue.m_strTagName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CXMLTree
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CXMLTree::CXMLTree(CString strName, CXMLTree *pParent)
	: CTree(CXMLData(strName), pParent, "XML tree")
{
	if (pParent != nullptr)
		pParent->AddChild(this);
}

CXMLTree::CXMLTree(CStringList strList, CXMLTree *pParent)
	: CTree(CXMLData(strList.front()), pParent, "XML tree")
{
	if (pParent != nullptr)
		pParent->AddChild(this);

	strList.pop_front();

	for (auto attribute : strList)
	{
		CStringList lst = attribute.Split('=');
		GetValueRef().m_mAttributes[lst.front()] = lst.back();
	}
}

CXMLTree::~CXMLTree()
{
}

CString CXMLTree::GetAttribute(CString const& strKey) const
{
	auto it = GetValueRef().m_mAttributes.find(strKey.ToLower());
	if (it == GetValueRef().m_mAttributes.end())
		return CString();

	return (*it).second;
}

CXMLTree* CXMLTree::Parse(std::istream &stream)
{
	CString strTag;
	CXMLTree *pCurrentNode = nullptr;

	while ((strTag = GetTag(stream)) != "")
	{
		CStringList lst = strTag.Split();

		if (lst.front()[0] == '/')
		{
			CString compare('/' + pCurrentNode->GetValueRef().m_strTagName);
			if (pCurrentNode == nullptr || lst.front() != compare)
			{
				delete pCurrentNode->GetRoot();
				throw CError(CString("Tag was not opened: <%>").Arg(lst.front()), EXCEPT_PATH);
			}

			if (pCurrentNode->GetParent() == nullptr)
				return pCurrentNode;

			pCurrentNode = dynamic_cast<CXMLTree *>(pCurrentNode->GetParent());
			continue;
		}

		if (pCurrentNode == nullptr)
		{
			pCurrentNode = new CXMLTree(lst);
			continue;
		}

		CXMLTree *pChild = new CXMLTree(lst, pCurrentNode);
		pCurrentNode = pChild;
	}

	return static_cast<CXMLTree *>(pCurrentNode->GetRoot());
}

CString CXMLTree::GetTag(std::istream &stream)
{
	char ch = 0;
	bool bOpened = false;
	CString result = "";

	while (stream.get(ch) && ch != '\0')
	{
		if (ch == '<')
		{
			if (bOpened)
			{
				stream.putback(ch);
				throw CError(CString("Invalid symbol in tag definition \"%\"").Arg(result), EXCEPT_PATH);
			}

			bOpened = true;
			continue;
		}

		if (bOpened)
		{
			if (ch == '>')
				break;

			result.push_back(ch);
		}
	}

	return result;
}