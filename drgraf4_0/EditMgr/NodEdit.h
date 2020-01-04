 // ELMouse.h : header file
//
#ifndef _NODEDIT_H 
#define _NODEDIT_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "mouse.h"
/////////////////////
#include "DrNode.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CNodEdit : public CMouse
{
public:

	CNodEdit();
//////////////////////////////////////
	DECLARE_SERIAL(CNodEdit)
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
	int					ShowNodeToEdit(CDrNode* pDrNode);

	
		
protected:


	void			SizeRectDlgEd(CRect& BoxRect);
	///////////////////////////////////////////////////////////////////////////// Node Edit
	void			ElementLeftDown_NOD(CPoint point);
	void			ElementLeftUp_NOD(CPoint point);
	int				LeftUp_NODE(CPoint point,BOOL bCNode);
	///////////////////////////////////////////////////////////////////////////// Node Move
	void			PrepareFor_Xlation(CNodCreOp& NodCreOp);
	int				LeftUp_NODE_PreMove(CPoint point,BOOL bCNode);
	int				LeftUp_NODE_DoneMove(CPoint point,BOOL bCNode);
	void			SetMouseWICFromNode(CDrNode* pDrNode,LPOINT3* pMouseWIC);
	void			SetNodeFromMouseWIC(CDrNode* pDrNode,LPOINT3* pMouseWIC);
	int				SetThirdCoordFromNode(CDrNode* pDrNode,long* Third);
	void			PostLeft();
	void			LMovDown_NOD(CPoint point);
	////////////////////////////////////////////////////////////////// Curve

protected:  
// Attributes


	///////////////////////////////////////////////////
	GENERATE	m_Gener;		// forward/reverse/auto					
	///////////////////////////////////////////
	int			m_nActiveObject;
	int			m_nActiveTool;
	/////////////////////////////////////////// Node 
	CDrNode*	m_pCurrentNode;
	/////////////////////////////////////////// Transformation Info
	BOOL		m_bCoordIn;		// for Translation Value
	CString		m_TranPtID;		// Grab
	WORLD		m_wTranPt;
	WORLD		m_wTran;
	WORLD		m_wFin_Tran;	// same as m_wTran



//Operations
public:

	~CNodEdit();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CNodEdit)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
