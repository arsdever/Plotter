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

#include "ctree.h"
#define FIND_BY_ARG(ARG, LIST)																\
	for (auto i : LIST)																		\
	{																						\
		if (i == ARG)																		\
			return i;																		\
	}																						\
	return nullptr

#define FIND_BY_VALUE(ARG, LIST)															\
	for (auto i : LIST)																		\
	{																						\
		if (i->m_tValue == ARG)																\
			return i;																		\
	}																						\
	return nullptr

#define FIND_IT(WHAT, WHERE, TYPE, NAME)													\
	typename std::list< TYPE >::const_iterator NAME = WHERE.cbegin();						\
	for (; NAME != WHERE.cend(); ++NAME)													\
	{																						\
		if ((*NAME) == WHAT)																\
			break;																			\
	}

template <typename T>
CTree<T>::CTree(CTree<T> *pParent, std::string strType)
	: IType(strType)
	, m_pParent(pParent)
{
	if(m_pParent != nullptr)
		m_pParent->AddChild(this);
}

template <typename T>
CTree<T>::CTree(T tValue, CTree<T> *pParent, std::string strType)
	: IType(strType)
	, m_pParent(pParent)
	, m_tValue(tValue)
{
	if(m_pParent != nullptr)
		m_pParent->AddChild(this);
}

template <typename T>
CTree<T>::~CTree()
{
	RemoveSubtree(this);
}

template<typename T>
CResult CTree<T>::AddChild(CTree<T> *pChild)
{
	CTree<T> *pNode = FindChild(pChild);

	if(pNode != nullptr)
		return CResult::EResultType(CResult::Fail | CResult::Already);

	m_lChildren.push_back(pChild);
	pChild->ChangeParent(this);

	return CResult::Success;
}

template<typename T>
CResult CTree<T>::RemoveChild(CTree<T> *pChild)
{
	CTree<T> *pNode = FindChild(pChild);
	
	if(pNode == nullptr)
		return CResult::Fail;

	RemoveNode(pNode);

	return CResult::Success;

}

template<typename T> inline
CResult CTree<T>::AddSibling(CTree<T> *pSibling)
{
	if (m_pParent == nullptr)
		return CResult::Fail;

	return m_pParent->AddChild(pSibling);
}

template<typename T> inline
CResult CTree<T>::RemoveSibling(CTree<T> *pSibling)
{
	if (GetParent() == nullptr)
		return CResult::Fail;

	return GetParent()->RemoveNode(pSibling);
}

template<typename T>
inline CResult CTree<T>::RemoveTree(CTree<T>* pNode)
{
	delete GetRoot();
	return CResult::Success;
}

template<typename T>
CResult CTree<T>::RemoveSubtree(CTree<T>* pNode)
{
	GetParent()->RemoveChild(this);

	for (auto it : m_lChildren)
		delete it;
	
	return CResult::Success;
}

template<typename T>
CResult CTree<T>::RemoveNode(CTree<T>* pNode)
{
	CTree<T> *pParent = pNode->GetParent();
	typename std::list<CTree<T> *>::const_iterator it = pNode->m_lChildren.cbegin();
	for (; it != pNode->m_lChildren.cend(); ++it)
	{
		pParent->AddChild((*it));
	}

	pNode->m_lChildren.clear();
	delete pNode;

	return CResult::Success;
}

template<typename T> inline
CResult CTree<T>::ChangeParent(CTree<T> *pParent)
{
	if (m_pParent == pParent)
		return CResult::EResultType(CResult::Fail | CResult::Already);

	pParent->AddChild(this);

	return CResult::Success;
}

template<typename T> inline
CTree<T>* CTree<T>::GetParent()
{
	return m_pParent;
}

template<typename T> inline
const CTree<T>* CTree<T>::GetParent() const
{
	return m_pParent;
}

template<typename T>
CTree<T>* CTree<T>::GetRoot()
{
	CTree<T> *pRoot = this;

	while (pRoot->GetParent() != nullptr)
	{
		pRoot = pRoot->GetParent();
	}

	return pRoot;
}

template<typename T>
const CTree<T>* CTree<T>::GetRoot() const
{
	const CTree<T> *pRoot = this;

	while (pRoot->GetParent() != nullptr)
	{
		pRoot = pRoot->GetParent();
	}

	return pRoot;
}

template<typename T>
inline CTree<T>* CTree<T>::GetNextSibling()
{
	if (m_pParent == nullptr)
		return nullptr;

	FIND_IT(this, m_pParent->m_lChildren, CTree<T> *, itThis);

	if (++itThis == m_pParent->m_lChildren.cend())
		return nullptr;

	return *itThis;
}

template<typename T>
inline const CTree<T>* CTree<T>::GetNextSibling() const
{
	if (m_pParent == nullptr)
		return nullptr;

	FIND_IT(this, m_pParent->m_lChildren, CTree<T> *, itThis);

	if (++itThis == m_pParent->m_lChildren.cend())
		return nullptr;

	return *itThis;
}

template<typename T>
CTree<T>* CTree<T>::GetPrevSibling()
{
	if (m_pParent == nullptr)
		return nullptr;

	FIND_IT(this, m_pParent->m_lChildren, CTree<T> *, itThis);

	if (itThis == m_pParent->m_lChildren.begin())
		return nullptr;

	return *(--itThis);
}

template<typename T>
const CTree<T>* CTree<T>::GetPrevSibling() const
{
	if (m_pParent == nullptr)
		return nullptr;

	FIND_IT(this, m_pParent->m_lChildren, CTree<T> *, itThis);

	if (itThis == m_pParent->m_lChildren.begin())
		return nullptr;

	return *(--itThis);
}

template<typename T> inline
CTree<T>* CTree<T>::GetFirstChild()
{
	return *m_lChildren.begin();
}

template<typename T> inline
const CTree<T>* CTree<T>::GetFirstChild() const
{
	return *m_lChildren.begin();
}

template<typename T> inline
CTree<T>* CTree<T>::GetLastChild()
{
	return *--m_lChildren.end();
}

template<typename T> inline
const CTree<T>* CTree<T>::GetLastChild() const
{
	return *--m_lChildren.end();
}


template<typename T>
CTree<T>* CTree<T>::FindChild(T const& tValue)
{
	FIND_BY_VALUE(tValue, m_lChildren);
}

template<typename T>
const CTree<T>* CTree<T>::FindChild(T const& tValue) const
{
	FIND_BY_VALUE(tValue, m_lChildren);
}

template<typename T>
CTree<T>* CTree<T>::FindChild(CTree<T> *pNode)
{
	FIND_BY_ARG(pNode, m_lChildren);
}

template<typename T>
const CTree<T>* CTree<T>::FindChild(CTree<T> *pNode) const
{
	FIND_BY_ARG(pNode, m_lChildren);
}

template<typename T>
const CTree<T>* CTree<T>::FindChild(const CTree<T> *pNode) const
{
	FIND_BY_ARG(pNode, m_lChildren);
}

template<typename T> inline
T& CTree<T>::GetValueRef()
{
	return m_tValue;
}

template<typename T> inline
const T& CTree<T>::GetValueRef() const
{
	return m_tValue;
}

template<typename T> inline
T CTree<T>::GetValue() const
{
	return m_tValue;
}

#undef FIND_BY_VALUE
#undef FIND_BY_ARG
#undef FIND_IT