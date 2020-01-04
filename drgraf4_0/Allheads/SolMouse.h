 // ELMouse.h : header file
//
#ifndef _SOLMOUSE_H 
#define _SOLMOUSE_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>			// CList Template
                    
#include "PatMouse.h"
///////////////////// Modeless
//#include "Dlg_SolI.h"
#include "Sheet_SOLI.h"
/////////////////////
#include "MI_Sol_I.h"
#include "DListMgr.h"
#include "Def_CuPS.h"                    
#include "Def_Type.h"                    
#include "Def_Mous.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CSolMouse : public CPatMouse
{
public:

	CSolMouse();
//////////////////////////////////////
	DECLARE_SERIAL(CSolMouse)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	int				CreateDataNodeList_Solid(CDListMgr* pNodeList,CDListMgr* pPatchList,
								  CList<PATCHLATCH,PATCHLATCH>*	pLatchList_U,
									int& nNodes_U,int& nNodes_V);
	/////////////////////////////////////////////////////////////////////////// Solid Topology
	int				SolTopo_Update(CDrSolid* pCurrentSolid,CDListMgr* pCurrentPatList,
						CDListMgr* pCurrentCurList,CDListMgr* pCurrentNodList);
	int				SolTopo_ConnectObjects(CDrSolid* pCurrentObject,CDListMgr* pList);
	///////////////////////////////////////////////////////////////////////////
	UINT			ReSetToolID_SOL(UINT CntlID,UINT IGenID, UINT OperID);
	void			InitDlgIn_SOL();
	void			ModeLessOff_SOL();
	void			ModeLessOn_SOL();
	////////////////////////////////////////////////////////
//	CDlg_SolI*		GetSolInDlg(){return m_pSolInDlg;};                                                                                
	CSheet_SOLI*	GetSolSheet(){return m_pSolInSheet;};                                                                                
	////////////////////////////////////////////////////////////////
	void			ResetVuBasedVars_SolDlg();
	long			CreateorActivateSolIn(UINT wParam, long lParam);
	long			CancelSolIn(UINT wParam, long lParam);
	long			GoodByeSolIn(UINT wParam, long lParam);
	long			UpdateSolIn(UINT wParam, long lParam);
	/////////////////////
	void 			OnEBoxMouseMove_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonDown_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonDown_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonUp_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonUp_SOL(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	/////////////////////////////////////////////////////////////////////////// SOLID
	virtual CString&	GetCurrentSolidID(){return m_CurrentSolidID;};
	virtual void		SetCurrentSolidID(CString Pid){m_CurrentSolidID = Pid;};
 	virtual SOLSUBTYPE	GetSolSubType(){return m_SolSubType;};
	virtual void		SetSolSubType(SOLSUBTYPE pst){m_SolSubType = pst;};
	

		
protected:


	void		Temp_FillOtherInfo_Tensor_SOL();
	////////////////////////////////////////
	void		ResetVariables_SOL();
	int			Terminate_SOL(BOOL bError);
	int			RightUp_Premature_SOL();
	int			RightUp_NotAutoAccept_SOL();
	int			ShowSolid(CString* pID);
	//////////////////////////////////////////////
	int			ElementLeftDown_SOL();				// described in derived also
	int			ElementLeftUp_SOL(CPoint point);	// described in derived also
	//////////////////////////////////////////////////////// Patch
	int			LeftUp_Sol_Patch(POINT point);
	int			LeftUp_Patch_Accept_OtherContext(CPoint point);
	int			ShowPatchInfo(CDrPatch* pDrPatch, char* buf, int jStart);
	int			LeftUp_Sol_Curve(POINT point);
	int			LeftUp_Sol_Node(CPoint point,BOOL bCNode,BOOL bDistinct,BOOL bNoOtherType);
	int			OldNode_N_Update_SOLContext(BOOL bCNode,BOOL bDistinct);
	//////////////////
	int			LeftDown_SOLID();
	int			LeftUp_EXTRUDE_SOL(POINT point);
	int			LeftUp_ROTATE_SOL(POINT point);
	int			LeftUp_DUCT_SOL(POINT point);
	int			LeftUp_SWEEP_SOL(POINT point);
	int			LeftUp_COONS_SOL(POINT point);
	/////////////////////////////////////////// 
	int			ProcessSolTwist_DUCT_SWEEP();
	int			ProcessSolScale_SWEEP();
	///////////////////////////////////////////
	int			LeftUp_LOFT_SOL(POINT point);
	///
	int			IsEndCondNeeded_LOFT_SOL(BOOL& bEndCondMode,
						int& nEndTanNeeded_U,int& nEndTanNeeded_V);
	int			GetBlendInfo_LOFT_SOL();
	///////////////////////////////////////////
	int			LeftUp_TENSOR_SOL(POINT point);
	///
	int			TENSORTwistDlgUpdate_SOL();
	int			TENSOREndDlgUpdate_SOL();
	int			IsEndCondNeeded_TENSOR_SOL(BOOL& bEndCondMode,
						int& nEndTanNeeded_U,int& nEndTanNeeded_V);
	int			GetBlendInfo_TENSOR_SOL();
	int			SwitchToEndCondDlg_SOL();
	int			UpdateEndDlg_TRUE_SOL();
	int			UpdateEndDlg_FALSE_SOL();
	int			UpdateTwistDlg_TRUE_SOL();
	int			UpdateTwistDlg_FALSE_SOL();
	///////////////////////////////////////////
	int			LeftUp_GORDON_SOL(POINT point);
	///
	int			GORDONEndDlgUpdate_SOL();
	int			IsEndCondNeeded_GORDON_SOL(BOOL& bEndCondMode,
						CDListMgr* pCurveList_U,CDListMgr* pCurveList_V);
	int			GetBlendInfo_GORDON_SOL();
	int			CheckCompatibility_GORDON_Solid(
						CDListMgr* pPatchList_U,CList<PATCHLATCH,PATCHLATCH>* pLatchList_U,
						CDListMgr* pPatchList_V,CList<PATCHLATCH,PATCHLATCH>* pLatchList_V);
	///////////////////////////////////////////
	int			CheckCompatibility_COONS_Solid(CDrCurve* pDrCurve,CURVELATCH& NewLat);
	//////
	int			ProcessSolRotAxis();
	int			UpdateSDlg_TRUE();
	int			UpdateSDlg_FALSE();
	int			UpdateSDlg_FALSE_EXTRUDE();
	int			UpdateSDlg_FALSE_ROTATE();
	int			UpdateSDlg_FALSE_LOFT();
	int			UpdateSDlg_FALSE_TENSOR();
	int			UpdateSDlg_FALSE_GORDON();
	int			UpdateSDlg_FALSE_COONS();
	int			UpdateSDlg_FALSE_DUCT();
	int			UpdateSDlg_FALSE_SWEEP();
	//////////////////////////////////////////////////
	int			ShowSolidInfo(CDrSolid* pDrSolid);
	//////////////////////////////////////////////////
	BOOL		IsEndCondNeeded_SOL();		// get BlendingInfo & Decide for EndCond


protected:  
// Attributes


	BOOL					m_bGenPat;
	CSheet_SOLI*			m_pSolInSheet;                                                                                
//	CDlg_SolI*				m_pSolInDlg; 
//	BOOL					m_bCurve; //Dlg.CID is used for both Patch or Curve			
	/////////////////////////////////////////// MousePost:MeshGeneration
//	CMI_Sol_P				m_MI_Sol_P;
	/////////////////////////////////////////// MouseInsert:Interpolate
	CMI_Sol_I				m_MI_Sol_I;
	/////////////////////////////////////////// Solid
	CDrSolid*				m_pCurrentSolid;
	CDrPatch*				m_pCurSolPatch;
	CDrPatch*				m_pOldSolPatch;
	CDrCurve*				m_pCurSolCurve;
	CDrCurve*				m_pOldSolCurve;
	//////////
	CDListMgr				m_PatchList;		// 
	CList<PATCHLATCH,PATCHLATCH>	m_PLatchList;	
//	CList<CURVELATCH,CURVELATCH>	m_LatchList;// already in PatMouse	
//	CDListMgr				m_NodeList;			// already in CurMouse
//	CList<int,int>			m_ElSegList			// already in CurMouse
	//////////
    int						m_LastSolidNum;		// internal
	SOLSUBTYPE				m_SolSubType;
	CString					m_CurrentSolidID;
	CString					m_CurrentSolidIDOld;
	BOOL					m_bSolidDone;		// for dragging
	int						m_nPatchDone;
	int						m_nInfoDone;
	//////////////////////////////// Dlg_SolI
	SOLIDPROC				m_SolProc;
	CString					m_Orient_P;
	CString					m_Orient_C;
	/////////////////////////////////////// Tensor
//	int						m_ElPerSeg; already in Curve
	int						m_ElPerSeg_W;
	int						m_nLastElems_W;	// if Closed
	BOOL					m_nNodeDone_V;
	int						m_nNodes_W;
	CDrCurve*				m_pBlendCurve_W;
	int						m_nBlendOrder_W;
	/////////////
	CList<int,int>			m_ElSegList_W;
	double					m_Ratio_W;
	///
	CList<BLENDEND,BLENDEND>
							m_EndList_W;	// if(bClosed_U or Linear_U,Circle_U,
											// parabola_U) EndList_U Empty
	/////////////
	int						m_nEndTanNeeded_W;
	BOOL					m_bV;				// TRUE:U_Dir/FALSE:V_Dir
	int						m_indexNode_J;		// Selected BndryNodeIndex in NodeList	
	//////////////////////////////////
	int						m_nCornerK;
	/////////////////////////////////////// Gordon
	BOOL					m_nPatchDone_U;
	BOOL					m_nPatchDone_V;
	int						m_nPatches_U;
	int						m_nPatches_V;
	int						m_nPatches_W;
	CDListMgr				m_PatchList_U;		// 
	CDListMgr				m_PatchList_V;		// 
	CDListMgr				m_PatchList_W;		// 
	CList<PATCHLATCH,PATCHLATCH>	m_PLatchList_U;	
	CList<PATCHLATCH,PATCHLATCH>	m_PLatchList_V;	
	CList<PATCHLATCH,PATCHLATCH>	m_PLatchList_W;	


//Operations
public:

	~CSolMouse();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CSolMouse)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
