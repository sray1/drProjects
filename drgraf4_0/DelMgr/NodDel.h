 // ELMouse.h : header file
//
#ifndef _NODDEL_H 
#define _NODDEL_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "mouse.h"
/////////////////////
#include "DrNode.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CNodDel : public CMouse
{
public:

	CNodDel();
//////////////////////////////////////
	DECLARE_SERIAL(CNodDel)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	///////////////////////////////////////////////////////////////////////////
	UINT				ReSetToolID_NOD(UINT CntlID,UINT IGenID, UINT OperID);
	/////////////////////
	void 				OnEBoxMouseMove_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 				OnEBoxLButtonDown_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 				OnEBoxRButtonDown_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 				OnEBoxLButtonUp_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 				OnEBoxRButtonUp_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	///////////////////////////////////////////////////// NODE
	int					ShowNodeToDelete(CDrNode* pDrNode, BOOL bToBeDeleted);
	int					MarkNode_Delete(CDrNode* pDrNode);

	
		
protected:


	///////////////////////////////////////////////////////// Node
	void			ElementLeftDown_NOD();
	void			ElementLeftUp_NOD(CPoint point);
	int				LeftUp_NODE(CPoint point,BOOL bCNode);
	//////////////////////////////////////////////////////

protected:  
// Attributes


	///////////////////////////////////////////////////
	GENERATE	m_Gener;		// forward/reverse/auto					
	///////////////////////////////////////////
	int			m_nActiveObject;
	int			m_nActiveTool;
	/////////////////////////////////////////// Node 
	CDrNode*	m_pCurrentNode;



//Operations
public:

	~CNodDel();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CNodDel)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
