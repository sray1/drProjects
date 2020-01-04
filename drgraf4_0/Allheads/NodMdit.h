 // ELMouse.h : header file
//
#ifndef _NODMDIT_H 
#define _NODMDIT_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "mouse.h"
/////////////////////
#include "DrFE0D.h" 	
#include "Def_IGen.h"	// MoveType	
#include "NodCreOM.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CNodMdit : public CMouse
{
public:

	CNodMdit();
//////////////////////////////////////
	DECLARE_SERIAL(CNodMdit)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	MOVETYPE			GetMoveType(){return m_MovTyp;};				// Move Type
	void				SetMoveType(MOVETYPE m){m_MovTyp = m;};		// Move Type
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
	int					ShowNodeToEdit(CDrFE0D* pDrNode);

	
		
protected:


	void			SizeRectDlgEd(CRect& BoxRect);
	///////////////////////////////////////////////////////////////////////////// Node Edit
	void			ElementLeftDown_NOD(CPoint point);
	void			ElementLeftUp_NOD(CPoint point);
	int				LeftUp_NODE(CPoint point,BOOL bCNode);
	///////////////////////////////////////////////////////////////////////////// Node Move
	void			PrepareFor_Xlation(CNodCreOM& NodCreOp);
	int				LeftUp_NODE_PreMove(CPoint point,BOOL bCNode);
	int				LeftUp_NODE_DoneMove(CPoint point,BOOL bCNode);
	void			SetMouseWICFromNode(CDrFE0D* pDrNode,LPOINT3* pMouseWIC);
	void			SetNodeFromMouseWIC(CDrFE0D* pDrNode,LPOINT3* pMouseWIC);
	int				SetThirdCoordFromNode(CDrFE0D* pDrNode,long* Third);
	void			PostLeft();
	void			LMovDown_NOD(CPoint point);
	////////////////////////////////////////////////////////////////// Curve

protected:  
// Attributes


	MOVETYPE	m_MovTyp;				// Move Type 	// in IGen.h
	BOOL		m_bMNode;	
	BOOL		m_bMCNode;	
	///////////////////////////////////////////////////
	GENERATE	m_Gener;		// forward/reverse/auto					
	///////////////////////////////////////////
	int			m_nActiveObject;
	int			m_nActiveTool;
	/////////////////////////////////////////// Node 
	CDrFE0D*	m_pCurrentNode;
	/////////////////////////////////////////// Transformation Info
	BOOL		m_bCoordIn;		// for Translation Value
	CString		m_TranPtID;		// Grab
	WORLD		m_wTranPt;
	WORLD		m_wTran;
	WORLD		m_wFin_Tran;	// same as m_wTran



//Operations
public:

	~CNodMdit();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CNodMdit)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
