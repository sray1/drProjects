 // ELMouse.h : header file
//
#ifndef _NODMOUAX_H 
#define _NODMOUAX_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>			// CList Template
                    
#include "mouse.h"
///////////////////// Modeless
#include "Dlg_NodI.h"
/////////////////////
#include "DrNode.h" 	
#include "DrLabel.h" 	
#include "DListMgr.h"
#include "Def_CuPS.h"                    
#include "Def_Type.h"                    
#include "Def_Mous.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CNodMouAX : public CMouse
{
public:

	CNodMouAX();
//////////////////////////////////////
	DECLARE_SERIAL(CNodMouAX)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	///////////////////////////////////////////////////////////////////////////
	UINT				ReSetToolID_NOD(UINT CntlID,UINT IGenID, UINT OperID);
	void				InitDlgIn_NOD();
	void				ModeLessOff_NOD();
	void				ModeLessOn_NOD();
	////////////////////////////////////////////////////////
	CDlg_NodI*			GetNodInDlg(){return m_pNodInDlg;};                                                                                
	////////////////////////////////////////////////////////////////
	long				CreateorActivateNodIn(UINT wParam, long lParam);
	long				CancelNodIn(UINT wParam, long lParam);
	long				GoodByeNodIn(UINT wParam, long lParam);
	long				UpdateNodIn(UINT wParam, long lParam);
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
	virtual	int 		ShowNode(CString* pID,BOOL bnid_c,int nHowMany);
	virtual CString		GetCurrentNodeID(){return m_CurrentNodeID;};
    virtual void		SetCurrentNodeID(CString NID)
    					{
    						m_CurrentNodeID = NID;
    					}; 
	virtual CString		GetAnchorNodeID(){return m_AnchorNodeID;};
	virtual void		SetAnchorNodeID(CString NID)
						{
							m_AnchorNodeID = NID;
						};

	
		
protected:


	//////////////////////////////////////////////
	void			SizeRectDlgIn(CRect& BoxRect);
	//////////////////////////////////////////////
	void			ElementLeftDown_NOD();				// described in derived also
	void			ElementLeftUp_NOD(CPoint point);	// described in derived also
	///////////////////////////////////////////////////////// Node
	CDrObject*		GetObjectFromID(CString& ID, int nObjType);
	void			SetMouseWICFromNode(CDrNode* pDrNode,LPOINT3* pMouseWIC);
	void			UpdateNDlg_TRUE();
	void			UpdateNDlg_FALSE();
	int				LeftUp_NODE(CPoint point,BOOL bCNode);
    ////////////////////////////////////////
	void 			SerializeNode(CArchive& ar);
	////////////////////////////////////
	void 			PreLeftDown(CPoint point);
	void 			PostLeft();
	void 			PreLeftUp(CPoint point);
	///////////////////////////////////////////////////////// ADVANCED Option
	void			Init_NOD();
	void			Terminate_NOD(BOOL bError);
	void			UpdateADlg_TRUE();
	void			UpdateDlg_TRUE_ADVANCE();
	void			UpdateADlg_FALSE();
	void			UpdateDlg_FALSE_ADVANCE();
	int				LeftUp_GetNode(POINT point, BOOL bCNode);
	int				LeftUp_GetNode_ADVANCE(POINT point, BOOL bCNode);
	int				LeftUp_ADVANCE_NOD(POINT point);
	int				LeftUp_Node_Accept(CPoint point,BOOL bCNode,BOOL bParent);
	int				ShowNotParentNodeInfo(CDrNode* pDrNode);
	int				RightUp_Premature();
	int				ShowInputInfo_NOD();
	int				ShowNodeInfo(CDrNode* pDrNode, char* buf, int jStart);
	int				ResolveReference_Direction();
	int				ResolveReference_Coords();
	int				UnitAxisFromEndNodes(pWORLD pNormal);
	int				RightUp_NotAutoAccept();
	//////////////////////////////////////////////////////////

protected:  
// Attributes


	CDlg_NodI*	m_pNodInDlg;                                                                                
	BOOL		m_bDoModalDone;
	///////////////////////////////////////////////////
	GENERATE	m_Gener;		// forward/reverse/auto					
	/////////////////////////////////////////// MouseInsert:Interpolate
//	CMI_Sol_I	m_MI_Sol_I;
	///////////////////////////////////////////
	BOOL    	m_bElementMode;
	int			m_nActiveObject;
	int			m_nActiveTool;
	/////////////////////////////////////////// Node 
	CDrNode*	m_pCurrentNode;
	CDrLabel*	m_pCurrentLabel;

    int			m_LastNodeNum;		// internal
	CString 	m_CurrentNodeID;
	CString 	m_CurrentNodeIDOld;
	CString 	m_AnchorNodeID;
	BOOL		m_bAnchorCNode;
	int			m_nNodeDone;		// for dragging
 	/////////////////////////////////////////// CNode     
	int		    m_nCNodeDone;		// for Curve & Patch
	CString 	m_CurrentCNodeID;
	///////////////////////////////////////////////////////// ADVANCED Option
	BOOL			m_bCorINodeOpDone;	// CNode or INode Hit Checking
	BOOL			m_bCNode;
	//////////////////////////////
	BOOL			m_bDlgExpect;
	/////////////////////////////////////////// Node
	CDrNode*		m_pSpawnedNode;
	CString			m_SpawnedNodeID;	//
	WORLD			m_wLoc;
	//////////
    int				m_LastNum;		// internal
	BOOL			m_bDone;		// for dragging
	int				m_nInfoDone;
	/////////////////////////////////////////// Dlg_NodI 
	CString			m_ObjID;
	double			m_X;
	double			m_Y;
	double			m_Z;		// also for other Coord
	double			m_dLength;
	CString			m_NID;
	//
	BOOL			m_bAdvanced;		// 
	BOOL			m_bIncrement;		// 
	BOOL			m_bDirection;		// 
	BOOL			m_bDirect;		// 
	BOOL			m_bDominant;	// Dialog info over Mouse
	/////////////////////////////
	CString			m_FromID;
	WORLD			m_wFrom;
	CString			m_ToID;
	WORLD			m_wTo;
	/////////////////////////////////////////// Advance Info
	WORLD			m_wInc;	// 
	WORLD			m_wFin;	// 
	CString			m_RefPtID;		// Reference Node
	WORLD			m_wRefPt;



//Operations
public:

	~CNodMouAX();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CNodMouAX)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
