// NodeBase.h : interface of the CNodeBase class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef NODEBASE_H
#define NODEBASE_H 
 
#include "node.h"
#include "globals.h"  

class CNodeBase : public CElemObject 
{

protected: // create from serialization only
	CNodeBase();
	DECLARE_DYNCREATE(CNodeBase)

// Attributes
public: 
	///////////////////////////////////////////////////// NODE
	POSITION	GetFirstNodePos();  				
	CDrNode*	GetNextNode( POSITION& pos);
	CDrNode* 	GetNode(int index);
	CDrNode*	NewNode();
    int			AddNode();
    int			EditNode(UINT index);
    int			DeleteNode(UINT index);
	int			GetNodeIndex(CString KeyID,UINT KeyNo); 
	int			GetNodeCount(){return m_NodeList.GetCount();};
	/////////////////////////////////////////////////////////////
protected:                  

	CObList	m_NodeList;
     
    ////////////////////////////////////// NODE
    NODECARD	m_CurrentNodeCard;
    UINT		m_MaxNodes;
    
// Operations
public:
// Implementation
public:
	virtual ~NodeBase();
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:
// Generated message map functions
protected:
	//{{AFX_MSG(CNodeBase)
	afx_msg LONG OnNode(UINT wParam,LONG lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
