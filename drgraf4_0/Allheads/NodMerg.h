 // ELMouse.h : header file
//
#ifndef _NODCREOP_H 
#define _NODCREOP_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>			// CList Template
                    
#include "Mouse.h"
///////////////////// Modeless
#include "Dlg_CrOi.h"
/////////////////////
#include "MatObj.h" 
////////////////////	
#include "DrNode.h" 	
#include "DrCurve.h"
#include "DrPatch.h"
#include "DrSolid.h"
#include "DrObj3D.h"
//////////////////// 	
#include "DrLabel.h" 	
#include "DListMgr.h"
#include "Def_IGen.h"   // Sym/Rot Type                
#include "Def_Type.h"                    
#include "Def_Mous.h"                    
#include "Def_IGen.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CNodCreOp : public CMouse
{
public:

	CNodCreOp();
//////////////////////////////////////
	DECLARE_SERIAL(CNodCreOp)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	XFORMTYPE		GetXfType(){return m_XfType;};			
	void			SetXfType(XFORMTYPE x){m_XfType = x;};
	SPAWNTYPE		GetSpnType(){return m_SpnType;};
	void			SetSpnType(SPAWNTYPE s){m_SpnType = s;};
	////////////////////////////
	void			InitDlgIn();
	////////////////////////////
	UINT			GetParentType(){return m_ParentType;};
	void			SetParentType(UINT p){m_ParentType = p;};
	CString&		GetstrParentType(){return m_strParentType;};
	void			SetstrParentType(CString& p){m_strParentType = p;};
	///////////////////////////////////////////////////////////////////////////
	UINT			ReSetToolID_NOD(UINT CntlID,UINT IGenID, UINT OperID);
	void			ModeLessOff();
	void			ModeLessOn();
	////////////////////////////////////////////////////////
	CDlg_CrOI*		GetCreOpDlg(){return m_pCreOpDlg;};                                                                                
	////////////////////////////////////////////////////////////////
	long			CreateorActivateCreOp_NOD(UINT wParam, long lParam);
	long			CancelCreOp_NOD(UINT wParam, long lParam);
	long			GoodByeCreOp_NOD(UINT wParam, long lParam);
	long			UpdateCreOp(UINT wParam, long lParam);
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
    ////////////////////////////////////////////////////////////////////// Transformation
	int				ShowInputInfo_XLATE();	// public for Edit & Move
	void			SetUpLocalM_XLATE();
	int				ShowNodeToSpawn(CDrNode* pParentNode,BOOL bUsingDlg);
	///////////////////////////////////////////////////////////////////// Transformation Info
	BOOL			IsCoordIn(){return m_bCoordIn;};		// for Translation Value
	void			SetCoordIn(BOOL b){m_bCoordIn = b;};		// for Translation Value
	CString&		GetTranPtID(){return m_TranPtID;};		// Grab
	void			SetTranPtID(CString& s){m_TranPtID =s;};// Grab
	WORLD&			GetTranPt(){return m_wTranPt;};
	void			SetTranPt(WORLD& w){m_wTranPt = w;};
	WORLD&			GetTran(){return m_wTran;};
	void			SetTran(WORLD& w){m_wTran = w;};
	WORLD&			GetFin_Tran(){return m_wFin_Tran;};
	void			SetFin_Tran(WORLD& w){m_wFin_Tran = w;};

	
protected:


	void		Init_NOD();
	void		Terminate_NOD(BOOL bError);
	//////////////////////////////////////////
	void		SizeRectDlgIn(CRect& BoxRect);
	///////////////////////////////
	int			RightUp_Premature();
	int			RightUp_NotAutoAccept();
	int			ShowPatch(CString* pID);
	//////////////////////////////////////////////
	void		ElementLeftDown_NOD();				// described in derived also
	void		ElementLeftUp_NOD(CPoint point);	// described in derived also
	//////////////////////////////////////////////////////// Patch
	int			LeftUp_Node(POINT point, BOOL bCNode);
	int			LeftUp_Node_Accept(CPoint point,BOOL bCNode,BOOL bParent);
	int			ShowNodeInfo(CDrNode* pDrNode, char* buf, int jStart);
	int			ShowParentNodeInfo(CDrNode* pDrNode);
	int			ShowNotParentNodeInfo(CDrNode* pDrNode);
	//////////////////
	int			LeftDown_NODE();
	int			LeftUp_GetNode_Parent(POINT point, BOOL bCNode);
	int			LeftUp_GetNode(POINT point, BOOL bCNode);
	
	void		UpdateDlg_TRUE();
	void		UpdateDlg_FALSE();
	void		UpdateDlg_FALSE_0();
	//////////////////////////////////////////////////////// Translate
	void		UpdateDlg_TRUE_XLATE();
	void		UpdateDlg_FALSE_XLATE();
	int			LeftUp_GetNode_XLATE(POINT point, BOOL bCNode);
	int			LeftUp_TRANSLATE_NOD(POINT point);
	//////////////////////////////////////////////////////// Rotate
	void		UpdateDlg_TRUE_ROTATE();
	void		UpdateDlg_FALSE_ROTATE();
	int			LeftUp_GetNode_ROTATE(POINT point, BOOL bCNode);
	int			LeftUp_ROTATE_NOD(POINT point);
	int			ShowInputInfo_ROTATE();
	int			CalcRotationFromDirCos(WORLD wDir); 
	int			CalcRotationFromFromTo(); 
	void		SetUpLocalM_ROTATE();
	//////////////////////////////////////////////////////// Scale
	void		UpdateDlg_TRUE_SCALE();
	void		UpdateDlg_FALSE_SCALE();
	int			LeftUp_GetNode_SCALE(POINT point, BOOL bCNode);
	int			LeftUp_SCALE_NOD(POINT point);
	int			ShowInputInfo_SCALE();
	void		SetUpLocalM_SCALE();
	//////////////////////////////////////////////////////// Reflect
	void		UpdateDlg_TRUE_REFLECT();
	void		UpdateDlg_FALSE_REFLECT();
	int			LeftUp_GetNode_REFLECT(POINT point, BOOL bCNode);
	int			LeftUp_REFLECT_NOD(POINT point);
	int			ShowInputInfo_REFLECT();
	void		SetUpLocalM_REFLECT();
	//////////////////////////////////////////////////////// Shear
	void		UpdateDlg_TRUE_SHEAR();
	void		UpdateDlg_FALSE_SHEAR();
	int			LeftUp_GetNode_SHEAR(POINT point, BOOL bCNode);
	int			LeftUp_SHEAR_NOD(POINT point);
	int			ShowInputInfo_SHEAR();
	void		SetUpLocalM_SHEAR();
	void		FormLocalM_Symm(pMATRIX pM);
	void		GetUnitNormal_Symm_N(pWORLD pNormal); 
	void		GetUnitNormal_Symm_3(pWORLD pNormal); 
	//////////////////////////////////////////////////////// Spawn
	int			LeftUp_NSPAWN(CPoint point);
	/////////////////////////////////////////////////////////////////////////////// Copy OFF
	int			ShowNodeToSpawnCopyOff(CDrNode* pParentNode,BOOL bUsingDlg);
	int			NodeSpawnCopyOff(CDrNode* pParentNode,BOOL bUsingDlg);
	///
	int			NodeDependent_SpawnConnectedObjects_CopyOff(CDrNode* pCurrentNode,BOOL bUsingDlg,
												UINT nObjType);
	///
	int			CurTopo_SpawnConnectedCurves_CopyOff(CDrCurve* pCurrentCurve,BOOL bUsingDlg);
	int			PatTopo_SpawnConnectedPatches_CopyOff(CDrPatch* pCurrentPatch,BOOL bUsingDlg);
	int			SolTopo_SpawnConnectedSolids_CopyOff(CDrSolid* pCurrentSolid,BOOL bUsingDlg);
	int			O3DTopo_SpawnConnectedObj3Ds_CopyOff(CDrObj3D* pCurrentObj3D,BOOL bUsingDlg);
	int			ShowObjectToSpawnCopyOff(CDrObject* pParentObject,BOOL bUsingDlg,UINT nObjType);
	///////////////////////////////////////////////////////////////////// Copy OFF Spawning
	CDListMgr*	GetNDoneList(){return &m_NDoneList;};
	CDListMgr*	GetCDoneList(){return &m_CDoneList;};
	CDListMgr*	GetPDoneList(){return &m_PDoneList;};
	CDListMgr*	GetSDoneList(){return &m_SDoneList;};
	CDListMgr*	GetODoneList(){return &m_ODoneList;};
	/////////////////////////////////////////////////////
	CMatObj*	GetMatObj(){return m_pMatObj;};
	void		SetMatObj(CMatObj* pMat){m_pMatObj = pMat;};




protected:  
// Attributes


	////////////////////////////////////////////////////// Copy OFF Spawning
	CDListMgr		m_NDoneList;
	CDListMgr		m_CDoneList;
	CDListMgr		m_PDoneList;
	CDListMgr		m_SDoneList;
	CDListMgr		m_ODoneList;
	////////////////////////////////
	CDrCurve*		m_pSpawnedCurve;
	////
	BOOL			m_bCorINodeOpDone;	// CNode or INode Hit Checking
	BOOL			m_bCNode;
	/////
	UINT			m_ParentType;		// NODE, CURVE etc
	CString			m_strParentType;
	//////////////////////////////
	BOOL			m_bDlgExpect;
	//////////////////////////////
	CDlg_CrOI*		m_pCreOpDlg;                                                                                
	BOOL			m_bDoModalDone;
	///////////////////////////////////////////////////
	GENERATE		m_Gener;		// forward/reverse/auto					
	/////////////////////////////////////////// MouseInsert:Interpolate
//	CMI_Sol_I	m_MI_Sol_I;
	///////////////////////////////////////////
	BOOL    		m_bElementMode;
	int				m_nActiveObject;
	int				m_nActiveTool;
	/////////////////////////////////////////// Node
	CDrNode*		m_pParentNode;
	CString			m_ParentID;
	CDrNode*		m_pSpawnedNode;
	CString			m_SpawnedID;	//
	CDrNode*		m_pCurrentNode;
	CString			m_CurrentNodeID;
	WORLD			m_wLoc;
	//////////
    int				m_LastNum;		// internal
	BOOL			m_bDone;		// for dragging
	int				m_nInfoDone;
	/////////////////////////////////////////// Dlg_CrOI 
	UINT			m_CreOp;
	CString			m_ObjID;
	double			m_X;
	double			m_Y;
	double			m_Z;		// also for other Coord
	CString			m_NID;
	BOOL			m_bDirect;		// both for Translation & Rotation & Reflection
	BOOL			m_bDominant;	// Dialog info over Mouse
				//12/29/97
	int				m_nAxis;
	BOOL			m_bNegative;
	BOOL			m_bAxis;
				//12/29/97 end
	/////////////////////////////////////////// Used for Both Tran & Rot
//	CString			m_FromID;
//	WORLD			m_wFrom;
//	CString			m_ToID;
//	WORLD			m_wTo;
	CString			m_FromID_R;		// Reference_Line Rot
	WORLD			m_wFrom_R;
	CString			m_ToID_R;
	WORLD			m_wTo_R;
	CString			m_FromID_T;		// Taget_Line Rot
	WORLD			m_wFrom_T;
	CString			m_ToID_T;
	WORLD			m_wTo_T;
	/////////////////////////////////////////// Transformation Info
	BOOL			m_bCoordIn;		// for Translation Value
	CString			m_TranPtID;		// Grab
	WORLD			m_wTranPt;
	WORLD			m_wTran;
	WORLD			m_wFin_Tran;	// same as m_wTran
	/////////////////////////////////////////// Rotation
	BOOL			m_bAngleIn;		// for Direct Rotation Angle		
	WORLD			m_wRot;
	BOOL			m_bOrigin;		// for Rotation about Origin		
	WORLD			m_wDir;
	CString			m_RotPtID;		// Grab
	WORLD			m_wRotPt;
	WORLD			m_wFin_Rot;
	/////////////////////////////////////////// Scale
	CString			m_ScalePtID;
	WORLD			m_wScalePt;
	WORLD			m_wScale;
	WORLD			m_wFin_Scale;	// same as m_wScale
	/////////////////////////////////////////// Reflection
	CString			m_SymmPtID[3];
	WORLD			m_wSymm[3];
	/////////////////////////////////////////// Shear
	CString			m_ShearPtID;
	WORLD			m_wShearPt;
	WORLD			m_wShear;
	WORLD			m_wFin_Shear;	// same as m_wShear
	/////////////////////////////////////////// Matrix etc
	CMatObj*		m_pMatObj;
	BOOL			m_bInstanced;
	BOOL			m_bNoTran;
	BOOL			m_bNoRot;
	BOOL			m_bNoScale;
	BOOL			m_bNoShear;
	XFORMTYPE		m_XfType;	// in IGen.h
	SPAWNTYPE		m_SpnType;	// in IGen.h


//Operations
public:

	~CNodCreOp();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CNodCreOp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
