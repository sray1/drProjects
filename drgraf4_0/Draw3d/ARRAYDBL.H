#ifndef	_WORLDARRAY_
#define	_WORLDARRAY_


#include "globals.h"
////////////////////////////////////////////////////////////////////////////

class CWorldArray : public CObject
{

	DECLARE_SERIAL(CWorldArray)
public:

// Construction
	CWorldArray();

// Attributes
	int GetSize() const;
	int GetUpperBound() const;
	void SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();

	// Accessing elements
	WORLD GetAt(int nIndex) const;
	void SetAt(int nIndex, WORLD newElement);
	WORLD& ElementAt(int nIndex);

	// Potentially growing the array
	void SetAtGrow(int nIndex, WORLD newElement);
	int Add(WORLD newElement);

	// overloaded operator helpers
	WORLD operator[](int nIndex) const;
	WORLD& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, WORLD newElement, int nCount = 1);
	void RemoveAt(int nIndex, int nCount = 1);
	void InsertAt(int nStartIndex, CWorldArray* pNewArray);

// Implementation
protected:
	WORLD* m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount

public:
	~CWorldArray();

	void Serialize(CArchive&);
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif
};


////////////////////////////////////////////////////////////////////////////
#endif