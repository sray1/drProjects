// World.h : interface of the CWorld class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef WORLD_H
#define WORLD_H 
 
#include "globals.h"  
#include "globals.h"  

class CWorld : public CGrafObject 
{

protected: // create from serialization only
	CWorld();
	DECLARE_DYNCREATE(CWorld)

// Attributes
public: 
					                               
protected:                  

    LONG	m_WorldBase;
    POINT3	m_WorldMouseLoc;
    POINT3	m_WorldMax;
    POINT3	m_WorldMin;
    POINT3	m_WorldOrigin;
    POINT3	m_WorldExtent;
	
// Operations
public:
    int 		GetNodeIndex(CString id);
    void 		DeleteNode(int index);
    int			AddNode(int n);
    CDrNode*	GetNode(int index);
    LONG		GetWorldBase(){return m_WorldBase;};
    UINT		GetMaxNodes(){return m_MaxNodes;};
// Implementation
public:
	virtual ~World();
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:
			void 	Initialize();
// Generated message map functions
protected:
	//{{AFX_MSG(CWorld)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
