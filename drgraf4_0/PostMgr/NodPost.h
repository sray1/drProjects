 // ELMouse.h : header file
//
#ifndef _NODPOST_H 
#define _NODPOST_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "mouse.h"
///////////////////// Modeless
#include "DrFE0D.h"
#include "Dlg_FE0i.h"
/////////////////////
//#include "DrBallJt.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CNodPost : public CMouse
{
public:

	CNodPost();
//////////////////////////////////////
	DECLARE_SERIAL(CNodPost)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	void			InitDlgIn_NOD();
	////////////////////////////
	UINT			GetParentType(){return m_ParentType;};
	void			SetParentType(UINT p){m_ParentType = p;};
	CString&		GetstrParentType(){return m_strParentType;};
	void			SetstrParentType(CString& p){m_strParentType = p;};
	////////////////////////////////
	UINT			ReSetToolID_NOD(UINT CntlID,UINT IGenID, UINT OperID);
	void			ModeLessOff_NOD();
	void			ModeLessOn_NOD();
	////////////////////////////////////////////////////////
	CDlg_FE0I*		GetPost0DDlg(){return m_pPost0DDlg;};                                                                                
	///////////////////////////////////////////////////////////////////////////
	long			CreateorActivatePost_NOD(UINT wParam, long lParam);
	long			CancelPost_NOD(UINT wParam, long lParam);
	long			UpdatePost_NOD(UINT wParam, long lParam);
	long			GoodByePost_NOD(UINT wParam, long lParam);
	/////////////////////
	void 			OnEBoxMouseMove_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
										UINT nFlags, CPoint point);
	void 			OnEBoxLButtonDown_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
										UINT nFlags, CPoint point);
	void 			OnEBoxRButtonDown_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
										UINT nFlags, CPoint point);
	void 			OnEBoxLButtonUp_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
										UINT nFlags, CPoint point);
	void 			OnEBoxRButtonUp_NOD(CClientDC* pdc,CView* pView,GENERATE gener,
										UINT nFlags, CPoint point);
	///////////////////////////////////////////////////// NODE

	
		
protected:


	void			Init_NOD();
	void			Terminate_NOD(BOOL bError);
	//////////////////////////////////////////
	int				UpdateSceneView(CString& ObjID,UINT nObjType);		
	void			SizeRectDlgIn(CRect& BoxRect);
	//////////////////////////////////////////////
	void			ElementLeftDown_NOD();
	void			ElementLeftUp_NOD(CPoint point);
	int				LeftUp_NODE(CPoint point,BOOL bCNode, BOOL bMNode);
	//////////////////////////////////////////////////
	void			UpdateDlg_TRUE_NOD();

	void			UpdateDlg_FALSE_NOD();
	void			UpdateDlg_FALSE_NOD_0();
	void			UpdateDlg_FALSE_BALLJOINT();
	//////////////////////////////////////////////
	int				RightUp_Premature_NOD();
	int				RightUp_NotAutoAccept_NOD();
	//////////////////////////////////////////////
	int				ShowNodeToPost(CDrNode* pDrNode, BOOL bToBePosted);
	//////////////////////////////////////////////////////
	int				ShowInputInfo_BALLJOINT();
	int				Post_BALLJOINT(CDrNode* pDrNode);
	/////////////////////////////////////////////////


protected:  
// Attributes


	UINT			m_ObjType;
	BOOL			m_bCNode;
	BOOL			m_bMNode;
	/////
	UINT			m_ParentType;	// NODE, CURVE etc
	CString			m_strParentType;
	//////////////////////////////
	CDlg_FE0I*		m_pPost0DDlg;                                                                                
	///////////////////////////////////////////////////
	GENERATE		m_Gener;		// forward/reverse/auto					
	///////////////////////////////////////////
	BOOL   			m_bElementMode;
	int				m_nActiveObject;
	int				m_nActiveTool;
	/////////////////////////////////////////// Node 
	CString			m_PostedID;
	CDrNode*		m_pParentNode;
	CString			m_ParentID;
	CDrFE0D*		m_pPostedNode;
	CDrNode*		m_pCurrentNode;
	//////////
    int				m_LastNum;		// internal
	BOOL			m_bDone;		// for dragging
	int				m_nInfoDone;
	/////////////////////////////////////////// FE0D Common Data Not Included Above
	CString			m_ElNumID;	
	CString			m_ElTypeID;			// TRUSS,BEAM,PIPE etc
	CString			m_rid_0;//			// For BallJoint
	CString			m_pid;  
	CString			m_mid;  
	////////////////////////////////// Indices in List
	UINT			m_ElNum;				// Element Number
	UINT			m_ElTypeNum;			// id Number: Element Type
	UINT			m_rel_0; 
	UINT			m_prop;           //
	UINT			m_mat;           //
	/////////////////////////
	double			m_refTemp;				//RefrenceTemperature
	////////////////////////////// 
	int				m_nCardNo;
	/////////////////////// Genetics
	UINT			m_GenObjType;	// Mesh0D,Mesh1D,Mesh2D or Mesh3D
	CDrObject*		m_pGenObj;
	///////////////////////



//Operations
public:

	~CNodPost();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CNodPost)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
