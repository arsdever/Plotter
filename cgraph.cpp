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

#include "cgraph.h"
#include "cxmltree.h"
#include "cexcept.h"

#include <map>
#include <queue>
#include <fstream>
#include <sstream>

#ifndef INT_MAX
#define INT_MAX 0x7fffffff
#endif

const std::string VertexNotFound = "Vertex not found.";
const std::string CGraph::SSignature::s_strFileTypeGraph = "GRAPH";
const std::string CGraph::SSignature::s_strFileTypeCommand = "COMMAND";
const std::string CGraph::SSignature::s_strFileTypeUserDef = "USERDEFINED";
const CGraph::SSignature CGraph::s_sSignature_V_1("GRAPH", 1, 0);

std::istream& operator >>(std::istream& strmInputStream, CVertexList &lVertexList)
{
	std::string strName;
	strmInputStream >> strName;
	lVertexList.push_back(new CVertex(strName));
	return strmInputStream;
}

OStream& operator <<(OStream& strmOutputStream, CVertexList const& lVertexList)
{
	strmOutputStream << "\nVertices list: {";
	VertexPtrList::const_iterator it = lVertexList.cbegin();
	for (unsigned i = 0; it != lVertexList.cend(); ++it, ++i)
	{
		i %= 6;

		if (!i)
			strmOutputStream << '\n';

		strmOutputStream << '\t' << (*it)->GetName();
	}

	return strmOutputStream << "\n}\n" << std::flush;
}


OStream& operator <<(OStream& strmOutputStream, CEdgeList const& lEdgesList)
{
	strmOutputStream << "\nEdges list: {" << std::endl;
	EdgePtrList::const_iterator it = lEdgesList.cbegin();
	for (; it != lEdgesList.cend(); ++it)
	{
		strmOutputStream << '\t' << (*it)->GetName() << " ( " << (*it)->GetVertexName1() << " , " << (*it)->GetVertexName2() << " )" << std::endl;
	}

	return strmOutputStream << "}\n" << std::flush;
}

std::string CVertexList::ToString() const
{
	std::stringstream strm;
	strm << *this;
	return strm.str();
}

CGraph::CGraph(std::string const& strName)
	:IType("graph")
	,m_strName(strName)
{
	s_lGraph.push_back(this);
}

CGraph::~CGraph()
{
	for (auto it : m_lVertexList)
	{
		delete it;
	}

	s_lGraph.remove(this);
}

CResult CGraph::AddEdge(CEdge *pEdge)
{
	if (pEdge == nullptr)
		return CResult::Fail;

	for (auto item : m_lEdgeList)
	{
		if (*item == *pEdge)
			return CResult::EResultType(CResult::Success | CResult::Already);
	}

	CVertex *pVertex1 = GetVertex(pEdge->GetVertexName1());
	CVertex *pVertex2 = GetVertex(pEdge->GetVertexName2());

	if (pVertex1 == nullptr || pVertex2 == nullptr)
		return CResult::Fail;

	m_lEdgeList.push_back(pEdge);

	pVertex1->AddNeighbour(pVertex2).Failure();
	pVertex2->AddNeighbour(pVertex1).Failure();

	return CResult::Success;
}

CResult CGraph::AddXEdge(CXEdge *pEdge)
{
	if (pEdge == nullptr)
		return CResult::Fail;

	for (auto item : m_lEdgeList)
	{
		if (*item == *pEdge)
			return CResult::EResultType(CResult::Success | CResult::Already);
	}

	CVertex *pVertex1 = GetVertex(pEdge->GetVertexName1());
	CVertex *pVertex2 = GetVertex(pEdge->GetVertexName2());

	if (pVertex1 == nullptr || pVertex2 == nullptr)
		return CResult::Fail;

	m_lEdgeList.push_back(pEdge);

	pVertex1->AddNeighbour(pVertex2).Failure();

	return CResult::Success;
}

CResult CGraph::RemoveEdge(CEdge *cEdge)
{
	m_lEdgeList.remove(cEdge);
	delete cEdge;
	return CResult::Success;
}

CResult CGraph::AddVertex(CVertex *pVertex)
{
	if (pVertex == nullptr)
		return CResult::Fail;

	for (auto item : m_lVertexList)
	{
		if (*item == *pVertex)
			return CResult::EResultType(CResult::Success | CResult::Already);
	}

	m_lVertexList.push_back(pVertex);

	return CResult::Success;
}

CResult CGraph::RemoveVertex(CVertex *cVertex)
{
	m_lVertexList.remove(cVertex);

	for (CEdgeList::const_iterator it = m_lEdgeList.cbegin(); it != m_lEdgeList.cend();)
	{
		if ((*it)->GetVertexName1() == cVertex->GetName() || (*it)->GetVertexName2() == cVertex->GetName())
		{
			CEdgeList::const_iterator cit = it++;
			m_lEdgeList.remove((*cit));
		}
		else
			++it;
	}

	delete cVertex;
	return CResult::Success;
}

CResult CGraph::SetName(std::string const & strName)
{
	if (m_strName == strName)
		return CResult::EResultType(CResult::Success | CResult::Already);

	m_strName = strName;
	return CResult::Success;
}

CResult CGraph::operator <<(std::istream &strmInputStream)
{
	char csSignature[4];
	strmInputStream.get(csSignature, 4);

	if (strcmp(csSignature, "GRP"))
		return CResult::EResultType(CResult::Fail | (CResult::UserMask & Signature));

	unsigned nVertexNumber;
	strmInputStream >> nVertexNumber;

	for (unsigned i = 0; i < nVertexNumber; ++i)
	{
		strmInputStream >> m_lVertexList;
	}

	return CResult::Success;
}

OStream& CGraph::operator >>(OStream &strmOutputStream) const
{
	strmOutputStream << "\nPrinting graph " << GetName() << ".\n--------------------------------------------------------" << std::flush;
	strmOutputStream << m_lVertexList;
	return strmOutputStream << m_lEdgeList << std::endl;
}

std::string CGraph::GetDefaultVertexName()
{
	return m_lVertexList.GetNextName();
}

CVertex * CGraph::GetVertex(std::string const& strVertexName)
{
	for (auto pVertex : m_lVertexList)
	{
		if (pVertex == nullptr)
			continue;

		if (pVertex->GetName() == strVertexName)
			return pVertex;
	}

	return nullptr;
}

CEdge* CGraph::GetEdge(std::string const& strEdgeName)
{
	for (auto it : m_lEdgeList)
	{
		if (it->GetName() == strEdgeName)
			return it;
	}

	return nullptr;
}

CEdge* CGraph::GetEdge(std::string const& strVertexName1, std::string const& strVertexName2)
{
	for (auto it : m_lEdgeList)
	{
		if ((it->GetVertexName1() == strVertexName1 && it->GetVertexName2() == strVertexName2)
			||(it->GetVertexName1() == strVertexName2 && it->GetVertexName2() == strVertexName1))
			return it;
	}

	return nullptr;
}

CVertexList* CGraph::FindPath(CWrappedVertexList *pWrappers, CVertex *pVertexBegin, CVertex *pVertexEnd, int nDepth) const
{
	if (pWrappers == nullptr)
		return nullptr;

	if (pVertexEnd == pVertexBegin)
	{
		CVertexList *pVertexList = new CVertexList;
		pVertexList->push_front(pVertexEnd);

		return pVertexList;
	}

	CVertexList *result = nullptr;

	for (auto neigh : pVertexBegin->NeighbourList())
	{
		if (!(*pWrappers)[pVertexBegin].SetDepth(nDepth).Failure())
			result = FindPath(pWrappers, neigh, pVertexEnd, nDepth + 1);

		if (result != nullptr)
		{
			result->push_front(pVertexBegin);
			return result;
		}
	}

	return result;
}

CVertexList* CGraph::FindSPath(CVertex *pVertexBegin, CVertex *pVertexEnd) const
{
	CWrappedVertexList *pWrappers = new CWrappedVertexList(GetVertexList());

	if (pWrappers == nullptr)
		return nullptr;

	Valualize(pWrappers, pVertexBegin, pVertexEnd);

	CVertexList* res = FindSource(pWrappers, pVertexBegin, pVertexEnd);
	delete pWrappers;
	return res;
}


CResult CGraph::FindVertex(CVertex *pVertex) const
{
	for (auto ptr : m_lVertexList)
	{
		if (ptr == pVertex)
			return CResult::Success;
	}

	return CResult::Fail;
}

CVertex* CGraph::FindVertex(std::string const& strVertexName) const
{
	for (auto ptr : m_lVertexList)
	{
		if (ptr->GetName() == strVertexName)
			return ptr;
	}

	return nullptr;
}

CResult CGraph::FindEdge(CEdge *pEdge) const
{
	for (auto ptr : m_lEdgeList)
	{
		if (ptr == pEdge)
			return CResult::Success;
	}

	return CResult::Fail;
}

CEdge* CGraph::FindEdge(std::string const& strEdgeName) const
{
	for (auto ptr : m_lEdgeList)
	{
		if (ptr->GetName() == strEdgeName)
			return ptr;
	}

	return nullptr;
}

CGraph* CGraph::FindGraph(std::string const& strGraphName)
{
	for (auto it : s_lGraph)
	{
		if (it->GetName() == strGraphName)
		{
			return it;
		}
	}

	return nullptr;
}

CResult CGraph::Save(std::ofstream &fOFile) const
{
	fOFile << s_sSignature_V_1;
	fOFile << m_strName << ' ' << m_lVertexList.size();

	for (CVertexList::const_iterator it = m_lVertexList.cbegin(); it != m_lVertexList.cend(); ++it)
	{
		fOFile << ' ' << (*it)->GetName();
	}

	fOFile << ' ' << m_lEdgeList.size();

	for (CEdgeList::const_iterator it = m_lEdgeList.cbegin(); it != m_lEdgeList.cend(); ++it)
	{
		fOFile << ' ' << (*it)->GetVertexName1() << ' ' << (*it)->GetVertexName2() << ' ' << (*it)->GetName();
	}

	fOFile << std::flush;
	fOFile.close();

	return CResult::Success;
}

CResult CGraph::Load(std::ifstream &fIFile)
{
	m_sSignature << fIFile;
	if (m_sSignature.m_strFileType == "COMMAND")
	{
		return LoadFromCommand(fIFile);
	}
	if (m_sSignature.m_strFileType == "USERDEFINED")
	{
		return LoadFromUserType(fIFile);
	}

	std::string name;
	unsigned unSize;
	fIFile >> name;
	if (FindGraph(name) != nullptr)
		CResult::Fail | CResult::Already;

	SetName(name);
	if (!(fIFile >> unSize))
		return CResult::Fail;

	for (unsigned i = 0; i < unSize; ++i)
	{
		fIFile >> m_lVertexList;
	}

	if (!(fIFile >> unSize))
		return CResult::Fail;

	for (unsigned i = 0; i < unSize; ++i)
	{
		CVertex *v_1, *v_2;
		fIFile >> name;
		v_1 = FindVertex(name);
		fIFile >> name;
		v_2 = FindVertex(name);
		fIFile >> name;

		if (v_1 == nullptr || v_2 == nullptr)
			return CResult::Fail;

		m_lEdgeList.push_back(new CEdge(name, v_1, v_2));

		v_1->AddNeighbour(v_2);
		v_2->AddNeighbour(v_1);
	}

	fIFile.close();

	return CResult::Success;
}

CResult CGraph::LoadXML(std::ifstream &fIFile)
{
	CXMLTree *pTree = CXMLTree::Parse(fIFile);

	if (pTree->GetName().ToLower() != "graph")
		return CResult::Fail;

	if (!SetName(pTree->GetAttribute("name")))
		if (!SetName(CGraph::GetDefaultGraphName()))
			throw CError(CString("Cannot generate graph name"), EXCEPT_PATH);

	CXMLTree *pNode = dynamic_cast<CXMLTree *>(pTree->GetFirstChild());

	while(pNode != nullptr)
	{
		if (pNode->GetName().ToLower() == "vertex")
			AddVertex(new CVertex(pNode->GetAttribute("name")));

		if (pNode->GetName().ToLower() == "edge")
			AddEdge(new CEdge(pNode->GetAttribute("name"), FindVertex(pNode->GetAttribute("vertex1")), FindVertex(pNode->GetAttribute("vertex2"))));

		pNode = dynamic_cast<CXMLTree *>(pNode->GetNextSibling());
	}

	return CResult::Success;
}

CResult CGraph::LoadFromCommand(std::ifstream &fIFile)
{
	// TODO: Not implemented yet

	return CResult::Success;
}

CResult CGraph::LoadFromUserType(std::ifstream &fIFile)
{
	std::string tmp;
	fIFile >> tmp;

	if (tmp != "GRAPHNAME:")
		return CResult::Fail;

	fIFile >> tmp;

	if (FindGraph(tmp) != nullptr)
		return CResult::EResultType(CResult::Fail | CResult::Already);

	SetName(tmp);
	fIFile >> tmp;

	if (tmp != "VERTICES:")
		return CResult::Fail;

	fIFile >> tmp;
	while (tmp != "EDGES:")
	{
		CVertex *pVertex = nullptr;
		pVertex = new CVertex(tmp);
		if(m_lVertexList.AddVertex(pVertex).Failure())
			delete pVertex;

		if (!(fIFile >> tmp)) break;
	}

	while (fIFile >> tmp)
	{
		CVertex *pVertex1 = FindVertex(tmp), *pVertex2 = nullptr;

		if (!(fIFile >> tmp))
			return CResult::Fail;

		pVertex2 = FindVertex(tmp);

		if (pVertex1 == nullptr || pVertex2 == nullptr)
			return CResult::Fail;

		if (!(fIFile >> tmp))
			return CResult::Fail;

		CEdge *pEdge = nullptr;

		pEdge = new CEdge(tmp, pVertex1, pVertex2);
		if(m_lEdgeList.AddEdge(pEdge).Failure())
			delete pEdge;

		pVertex1->AddNeighbour(pVertex2);
		pVertex2->AddNeighbour(pVertex1);
	}

	return CResult::Success;
}

void CGraph::Valualize(CWrappedVertexList * pWrapper, CVertex * pSource, CVertex * pTarget) const
{
	std::queue<CVertex *> queue;
	(*pWrapper)[pSource].SetDepth(0);
	unsigned nDepth = 1;
	queue.push(pSource);

	while (!queue.empty())
	{
		CVertex * pVertex = queue.front();
		queue.pop();

		for (auto vertex : pVertex->NeighbourList())
		{
			if((*pWrapper)[vertex].SetDepth((*pWrapper)[pVertex].GetDepth() + 1))
				queue.push(vertex);

			if (vertex == pTarget)
				return;
		}
	}
}

CVertexList * CGraph::FindSource(CWrappedVertexList * pWrapper, CVertex * pSource, CVertex * pTarget) const
{
	if (pTarget == pSource)
	{
		CVertexList * result = new CVertexList();
		result->push_back(pTarget);
		return result;
	}

	for (auto vertex : pTarget->NeighbourList())
	{
		if ((*pWrapper)[pTarget].GetDepth() == (*pWrapper)[vertex].GetDepth() + 1)
		{
			CVertexList * res = FindSource(pWrapper, pSource, vertex);

			if (res != nullptr)
			{
				res->push_back(pTarget);
				return res;
			}
			else
				return nullptr;
		}
	}
	
	return nullptr;
}

CWrappedVertexList::CWrappedVertexList(CVertexList const& lstVertices)
{
	for (auto it : lstVertices)
	{
		push_back(CVertexWrapper(it, -1));
	}
}

int CWrappedVertexList::indexOf(CVertex *pVertex)
{
	int i = 0;
	const_iterator it = cbegin();
	for (; it != cend(); ++it, ++i)
	{
		if ((*it) == pVertex)
			return i;
	}

	return -1;
}

CVertexWrapper& CWrappedVertexList::operator [] (unsigned nIndex)
{
	int i = 0;
	iterator it = begin();
	for (; it != end(); ++it, ++i)
	{
		if (i == nIndex)
			break;
	}

	if (it == end())
		throw CError(CString("Index is out of ranges"));
	return *it;
}

std::string CGraph::GetDefaultGraphName()
{
	std::string result = "G_";

	while (IsExist(result + std::to_string(s_nDefaultNameIndex)))
	{
		++s_nDefaultNameIndex;
	}

	result += std::to_string(s_nDefaultNameIndex);

	return result;
}

std::string CGraph::GetDefaultEdgeName()
{
	return m_lEdgeList.GetNextName();
}

GraphPtrList CGraph::s_lGraph;
int CGraph::s_nDefaultNameIndex = 0;

bool CGraph::IsExist(std::string const& strName)
{
	for (GraphPtrList::const_iterator it = s_lGraph.begin(); it != s_lGraph.end(); ++it)
	{
		if ((*it)->GetName() == strName)
			return true;
	}

	return false;
}
CGraph* CGraph::GetGraphByName(std::string const& strName)
{
	for (GraphPtrList::const_iterator it = s_lGraph.begin(); it != s_lGraph.end(); ++it)
	{
		if ((*it)->GetName() == strName)
			return (*it);
	}

	return nullptr;
}

std::string CVertexList::GetNextName()
{
	std::string result = "V_";

	for (VertexPtrList::const_iterator it = cbegin(); it != cend(); ++it)
	{
		if ((*it)->GetName() == (result + std::to_string(m_nDefaultNameIndex)))
		{
			++m_nDefaultNameIndex;
			it = cbegin();
		}
	}

	result += std::to_string(m_nDefaultNameIndex);

	return result;
}

CResult CVertexList::AddVertex(CVertex * const pVertex)
{
	if (std::find(cbegin(), cend(), pVertex) != cend())
		return CResult::EResultType(CResult::Fail | CResult::Already);

	push_back(pVertex);
	return CResult::Success;
}

std::string CEdgeList::GetNextName()
{
	std::string result = "E_";

	for (EdgePtrList::const_iterator it = cbegin(); it != cend(); ++it)
	{
		if ((*it)->GetName() == (result + std::to_string(m_nDefaultNameIndex)))
		{
			++m_nDefaultNameIndex;
			it = cbegin();
		}
	}

	result += std::to_string(m_nDefaultNameIndex);

	return result;
}

CResult CEdgeList::AddEdge(CEdge *const pEdge)
{
	if (std::find(cbegin(), cend(), pEdge) != cend())
		return CResult::EResultType(CResult::Fail | CResult::Already);

	push_back(pEdge);

	return CResult::Success;
}

CEdge::CEdge(std::string strName, CVertex * pVertex1, CVertex * pVertex2)
	:m_pVertex1(pVertex1)
	,m_pVertex2(pVertex2)
	,m_strName(strName)
{
}

CEdge::~CEdge()
{
	CResult result1 = m_pVertex1->RemoveNeighbour(m_pVertex2);
	CResult result2 = m_pVertex2->RemoveNeighbour(m_pVertex1);
}

CResult CVertex::AddNeighbour(CVertex *pNeighbour)
{
	for (Neighbours::const_iterator it = m_plNeighbours.begin(); it != m_plNeighbours.end(); ++it)
	{
		if ((*it) == pNeighbour)
			return CResult::EResultType(CResult::Fail | CResult::Already);
	}

	m_plNeighbours.push_back(pNeighbour);
	return CResult::Success;
}

CResult CVertex::RemoveNeighbour(CVertex *pNeighbour)
{
	m_plNeighbours.remove(pNeighbour);

	return CResult::Success;
}

CResult CVertexWrapper::SetDepth(unsigned nValue)
{
	if (m_nValue <= nValue)
		return CResult::Fail;

	m_nValue = nValue;

	return CResult::Success;
}

bool CVertexWrapper::operator==(CVertex *pRef) const
{
	if (m_pVertex == pRef)
		return true;

	return false;
}
bool CVertexWrapper::operator ==(CVertexWrapper const& pRef) const
{
	if (pRef.m_pVertex == m_pVertex)
		return true;

	return false;
}

bool CGraph::SSignature::operator == (SSignature const& sSign)
{
	return (m_strFileType == sSign.m_strFileType) && (m_nMajorVersion == sSign.m_nMajorVersion) && (m_nMinorVersion == sSign.m_nMinorVersion);
}

std::ostream& operator << (std::ostream &strm, CGraph::SSignature const& ssign)
{
	return strm << "FILETYPE: " << ssign.m_strFileType << std::endl << "VERSION: " << ssign.m_nMajorVersion << '.' << ssign.m_nMinorVersion << std::endl << "DATA: ";
}

CResult CGraph::SSignature::operator << (std::istream &strm)
{
	std::string temp;
	strm >> temp;

	if (temp != "FILETYPE:")
		return CResult::Fail;

	strm >> temp;
	m_strFileType = temp;
	strm >> temp;

	if (temp != "VERSION:")
		return CResult::Fail;

	double version;

	if (!(strm >> version))
		return CResult::Fail;

	m_nMajorVersion = (int)version;
	version -= m_nMajorVersion;
	m_nMinorVersion = (int)(version * 1000);

	strm >> temp;

	if (temp != "DATA:")
		return CResult::Fail;

	return CResult::Success;
}

std::string CGraph::ToString() const
{
	std::stringstream strm;
	*this >> strm;
	return strm.str();
}

CXEdge::CXEdge(std::string strName, CVertex * pVertex1, CVertex * pVertex2)
	: CEdge(strName, pVertex1, pVertex2)
{}

CXEdge::~CXEdge()
{
	CResult result1 = m_pVertex1->RemoveNeighbour(m_pVertex2);
}

void Concate(CVertexList & lDest, CVertexList const & lSource, bool bRemove = true)
{
	if (bRemove && lDest.back() == lSource.front())
		lDest.pop_back();

	for (CVertexList::const_iterator it = lSource.cbegin(); it != lSource.cend(); ++it)
	{
		lDest.push_back(*it);
	}
}
