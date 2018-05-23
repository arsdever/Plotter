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

#ifndef CTREE_H
#define CTREE_H

#include "cresult.h"
#include <string>
#include <list>

template <typename T>
class CTree : public IType
{
public:
	// Constructor
	CTree(CTree<T> *pParent, std::string strType = "tree node");
	// Constructor
	CTree(T tValue, CTree<T> *pParent, std::string strType = "tree node");
	// Destructor
	// Clear subtree and delete node
	virtual ~CTree();
	
	// Add child node to tree
	virtual CResult AddChild(CTree<T> *pChild);
	// Remove child node from tree
	virtual CResult RemoveChild(CTree<T> *pChild);

	// Add sibling node to tree
	inline virtual CResult AddSibling(CTree<T> *pSibling);
	// Remove sibling node from tree
	inline virtual CResult RemoveSibling(CTree<T> *pSibling);

	// Remove whole tree that contains given node
	inline CResult RemoveTree(CTree<T> *pNode);
	// Remove subtree starting at given node
	CResult RemoveSubtree(CTree<T> *pNode);
	// Remove given node and update references
	CResult RemoveNode(CTree<T> *pNode);

	// Change parent
	inline virtual CResult ChangeParent(CTree<T> *pParent);

	// Get parent node
	inline virtual CTree<T>* GetParent();
	// Get parent node
	inline virtual const CTree<T>* GetParent() const;
	// Get root node
	virtual CTree<T>* GetRoot();
	// Get root node
	virtual const CTree<T>* GetRoot() const;
	// Get next sibling
	virtual CTree<T>* GetNextSibling();
	// Get next sibling
	virtual const CTree<T>* GetNextSibling() const;
	// Get previous sibling
	virtual CTree<T>* GetPrevSibling();
	// Get previous sibling
	virtual const CTree<T>* GetPrevSibling() const;
	// Get first child from children list
	virtual inline CTree<T>* GetFirstChild();
	// Get first child from children list
	virtual inline const CTree<T>* GetFirstChild() const;
	// Get last child from children list
	virtual inline CTree<T>* GetLastChild();
	// Get last child from children list
	virtual inline const CTree<T>* GetLastChild() const;

	// Find child by value
	virtual CTree<T>* FindChild(T const& tValue);
	// Find child by value
	virtual const CTree<T>* FindChild(T const& tValue) const;
	// Find child by pointer
	virtual CTree<T>* FindChild(CTree<T> *pNode);
	// Find child by pointer
	virtual const CTree<T>* FindChild(CTree<T> *pNode) const;
	// Find child by pointer
	virtual const CTree<T>* FindChild(const CTree<T> *pNode) const;

	virtual inline T& GetValueRef();
	virtual inline const T& GetValueRef() const;
	virtual inline T GetValue() const;

private:
	CTree<T> *m_pParent;
	T m_tValue;
	std::list<CTree<T> *> m_lChildren;
};

#include "ctree_impl.h"

#endif