#ifndef CGRAPH_H
#define CGRAPH_H

#include <iostream>
#include <string.h>
#include <list>
#include "itype.h"
#include "cresult.h"

class CVertex;
class CGraph;
class CEdge;

typedef std::list<CVertex *> VertexPtrList;
typedef std::list<CEdge *> EdgePtrList;
typedef std::list<CGraph *> GraphPtrList;
typedef std::ostream OStream;

class CVertex final
{
	typedef std::list<CVertex *> Neighbours;

private:
	// Name of vertex
	std::string m_strName;
	// List of pointers of neighbour vertexs
	Neighbours m_plNeighbours;

public:
	// Constructor
	CVertex(std::string const& strName = "")
		: m_strName(strName)
	{}
	// Destructor
	~CVertex() = default;

	// Add neighbour to vertex
	CResult AddNeighbour(CVertex *pNeighbour);
	// Remove neighbour from list
	CResult RemoveNeighbour(CVertex *pNeighbour);
	// Get neighbour list for vertex
	inline const Neighbours& NeighbourList() const { return m_plNeighbours; }
	// Get vertex of vertex
	inline std::string const& GetName() const { return m_strName; }
	// Set vertex of vertex
	inline CResult SetName(std::string const& strName) { m_strName = strName; }
	// operator ==
	inline bool operator == (CVertex const& cRef) { return m_strName == cRef.m_strName; }
};

class CVertexWrapper
{
public:
	// Constructor
	CVertexWrapper(CVertex *pVertex, unsigned nValue = -1)
		: m_pVertex(pVertex)
		, m_nValue(nValue)
	{}

	CResult SetDepth(unsigned nValue);
	inline unsigned GetDepth() const { return m_nValue; }

	bool operator ==(CVertex *pRef) const;
	bool operator ==(CVertexWrapper const& pRef) const;

private:
	// Vertex will be wrapped
	CVertex *m_pVertex;
	// Vertex value
	unsigned m_nValue;
};

class CEdge
{
protected:
	CVertex * m_pVertex1;
	CVertex* m_pVertex2;
	std::string m_strName;

public:
	// Constructor
	CEdge(std::string strName, CVertex* pVertex1, CVertex* pVertex2);
	// Destructor
	~CEdge();

	// Set vertex
	inline CResult SetName(std::string const& strName)
	{
		m_strName = strName;
		return CResult::Success;
	}
	// Get vertex
	inline std::string GetName() const { return m_strName; }
	// Get node1 vertex
	inline std::string GetVertexName1() const { return (m_pVertex1 == nullptr) ? "" : m_pVertex1->GetName(); }
	// Get node2 vertex
	inline std::string GetVertexName2() const { return (m_pVertex2 == nullptr) ? "" : m_pVertex2->GetName(); }
	// operator ==
	inline bool operator == (CEdge const& cRef) { return (m_pVertex1 == cRef.m_pVertex1 && m_pVertex2 == cRef.m_pVertex2) || (m_pVertex1 == cRef.m_pVertex2 && m_pVertex2 == cRef.m_pVertex1); }
};

class CXEdge : public CEdge
{
public:
	// Constructor
	CXEdge(std::string strName, CVertex* pVertex1, CVertex* pVertex2);
	// Destructor
	~CXEdge();
};

class CVertexList : public VertexPtrList
{
	unsigned m_nDefaultNameIndex;
public:
	// Constructor
	CVertexList()
		:m_nDefaultNameIndex(0)
	{}
	// Destructor
	~CVertexList() = default;

	// Get next default valid vertex name
	std::string GetNextName();
	// Add vertex to list if doesn't exist
	CResult AddVertex(CVertex *const pVertex);
	// Convert to string
	std::string ToString() const;

	// Serialization
	friend std::istream& operator >> (std::istream &strmInputStream, CVertexList &lVertexList);
	// Deserialization
	friend OStream& operator << (OStream &strmOutputStream, CVertexList const& lVertexList);
};

class CWrappedVertexList : public std::list<CVertexWrapper>
{
public:
	CWrappedVertexList(CVertexList const& lstVertices);

	int indexOf(CVertex *pVertex);
	CVertexWrapper& operator [](unsigned nIndex);
};

class CEdgeList : public EdgePtrList
{
	unsigned m_nDefaultNameIndex;
public:
	// Constructor
	CEdgeList()
		:m_nDefaultNameIndex(0)
	{}
	// Destructor
	~CEdgeList() = default;
	// Get next default vertex
	std::string GetNextName();
	// Add edge to list if doesn't exist
	CResult AddEdge(CEdge *const pEdge);

	// Serialization
	friend std::istream& operator >> (std::istream &strmInputStream, CEdgeList &lEdgeList);
	// Deserialization
	friend OStream& operator << (OStream &strmOutputStream, CEdgeList const& lEdgeist);
};

class CGraph : public IType
{
public:
	// Signature structure
	struct SSignature{
		static const std::string s_strFileTypeGraph;
		static const std::string s_strFileTypeCommand;
		static const std::string s_strFileTypeUserDef;

		std::string m_strFileType;
		int m_nMajorVersion;
		int m_nMinorVersion;

		SSignature(std::string strFileType = "GRAPH", int nMajor = 1, int nMinor = 0)
			: m_strFileType(strFileType)
			, m_nMajorVersion(nMajor)
			, m_nMinorVersion(nMinor)
		{}

		bool operator == (SSignature const& sSign);
		friend std::ostream& operator << (std::ostream &strm, SSignature const& ssign);
		CResult operator << (std::istream &strm);
	};

public:
	// Constructor
	CGraph(std::string const& strName = "");
	// Destructor
	virtual ~CGraph();

	// Add vertex
	CResult AddVertex(CVertex *cVertex);
	// Remove vertex
	CResult RemoveVertex(CVertex *cVertex);

	// Add edge
	CResult AddEdge(CEdge *pEdge);
	// Add xedge
	CResult AddXEdge(CXEdge *pEdge);
	// Remove edge
	CResult RemoveEdge(CEdge *cEdge);

	// Set graph vertex
	CResult SetName(std::string const& strName);
	// Get graph vertex
	inline std::string GetName() const { return m_strName; }
	// Get default vertex vertex
	std::string GetDefaultVertexName();
	// Get default edge vertex
	std::string GetDefaultEdgeName();
	// Get vertex by vertex
	CVertex* GetVertex(std::string const& strVertexName);
	// Get vertex list
	inline const CVertexList& GetVertexList() const { return m_lVertexList; }
	// Get edge by edge name
	CEdge* GetEdge(std::string const& strEdgeName);
	// Get edge by vertices names
	CEdge* GetEdge(std::string const& strVertexName1, std::string const& strVertexName2);

	// Find first path form begin vertex to end vertex
	CVertexList* FindPath(CWrappedVertexList *pWrappers, CVertex *pVertexBegin, CVertex *pVertexEnd, int nDepth = 0) const;
	// Find shortest path form begin vertex to end vertex
	CVertexList* FindSPath(CWrappedVertexList *pWrappers, CVertex *pVertexBegin, CVertex *pVertexEnd, int nDepth = 0) const;
	// Find vertex
	CResult FindVertex(CVertex *pVertex) const;
	// Find vertex by name
	CVertex* FindVertex(std::string const& strVertexName) const;
	// Find edge
	CResult FindEdge(CEdge *pEdge) const;
	// Find edge by name
	CEdge* FindEdge(std::string const& strEdgeName) const;
	// Find graph by name
	static CGraph* FindGraph(std::string const& strGraphName);

	// Save to file
	CResult Save(std::ofstream &fOFile) const;
	// Load from file
	CResult Load(std::ifstream &fIFile);
	// Load from xml file
	CResult LoadXML(std::ifstream &fIFile);
	// Load from command file
	CResult LoadFromCommand(std::ifstream &fIFile);
	// Load from user type file
	CResult LoadFromUserType(std::ifstream &fIFile);

	// Serialization
	CResult operator << (std::istream &strmInputStream);
	// Deserialization
	virtual OStream& operator >> (OStream &strmOutputStream) const;

	// Convert to string
	std::string ToString() const;

public:
	// Checks if graph vertex exist
	static bool IsExist(std::string const& strName);
	// Return graph pointer by vertex
	static CGraph* GetGraphByName(std::string const& strName);
	// Get default graph vertex
	static std::string GetDefaultGraphName();
	// Get graph list
	inline static GraphPtrList GetGraphList() { return s_lGraph; }

public:
	static const SSignature s_sSignature_V_1;

private:
	static GraphPtrList s_lGraph;
	static int s_nDefaultNameIndex;

	enum EResult
	{
		Signature = 0x00010000
	};

	CVertexList m_lVertexList;
	CEdgeList m_lEdgeList;
	std::string m_strName;
	SSignature m_sSignature;
};

#endif