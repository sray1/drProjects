 // ELMouse.h : header file
//
#ifndef _PATMOUSE_H 
#define _PATMOUSE_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>			// CList Template
                    
#include "CurMouse.h"
///////////////////// Modeless
//#include "Dlg_PatI.h"
#include "Sheet_PATI.h"
/////////////////////
#include "DrNode.h" 	
#include "DrLabel.h" 	
#include "DrCurve.h" 	
//#include "MI_Pat_P.h"
#include "MI_Pat_I.h"
#include "DListMgr.h"
#include "Def_CuPS.h"                    
#include "Def_Type.h"                    
#include "Def_Mous.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CPatMouse : public CCurMouse
{
public:

	CPatMouse();
//////////////////////////////////////
	DECLARE_SERIAL(CPatMouse)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	int				CreateDataNodeList(CDListMgr* pNodeList,CDListMgr* pCurveList,
								  CList<CURVELATCH,CURVELATCH>*	pLatchList_U,
									int& nNodes_U,int& nNodes_V);
	////////////////////////////////////////////////////////////////////// Pat Topology
	int				PatTopo_Update(CDrPatch* pCurrentPatch,CDListMgr* pCurList,
										CDListMgr* pNodList/*m_NodeList*/);
	int				PatTopo_ConnectObjects(CDrPatch* pCurrentObject,CDListMgr* pList);
	///////////////////////////////////////////////////////////////////////////
	UINT			ReSetToolID_PAT(UINT CntlID,UINT IGenID, UINT OperID);
	void			InitDlgIn_PAT();
	void			ModeLessOff_PAT();
	void			ModeLessOn_PAT();
	////////////////////////////////////////////////////////
//	CDlg_PatI*		GetPatInDlg(){return m_pPatInDlg;};                                                                                
	CSheet_PATI*	GetPatSheet(){return m_pPatInSheet;};                                                                                
	////////////////////////////////////////////////////////////////
	void			ResetVuBasedVars_PatDlg();
	long			CreateorActivatePatIn(UINT wParam, long lParam);
	long			CancelPatIn(UINT wParam, long lParam);
	long			GoodByePatIn(UINT wParam, long lParam);
	long			UpdatePatIn(UINT wParam, long lParam);
	/////////////////////
	void 			OnEBoxMouseMove_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonDown_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonDown_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonUp_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonUp_PAT(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
    ////////////////////////////////////////////////////////////////////// PATCH
	virtual CString&	GetCurrentPatchID(){return m_CurrentPatchID;};
	virtual void		SetCurrentPatchID(CString Pid){m_CurrentPatchID = Pid;};
 	virtual PATSUBTYPE	GetPatSubType(){return m_PatSubType;};
	virtual void		SetPatSubType(PATSUBTYPE pst){m_PatSubType = pst;};
	



protected:


	void		Temp_FillOtherInfo_Tensor();
	////////////////////////////////////////
	void		ResetVariables_PAT();
	int			Terminate_PAT(BOOL bError);
	int			RightUp_Premature_PAT();
	int			RightUp_NotAutoAccept_PAT();
	int			ShowPatch(CString* pID);
	//////////////////////////////////////////////
	int			ElementLeftDown_PAT();				// described in derived also
	int			ElementLeftUp_PAT(CPoint point);	// described in derived also
	//////////////////////////////////////////////////////// Patch
	int			LeftUp_Pat_Curve(POINT point);
	int			LeftUp_Pat_Node(CPoint point,BOOL bCNode,BOOL bDistinct,BOOL bNoOtherType);
	int			OldNode_N_Update_PATContext(BOOL bCNode,BOOL bDistinct);
	int			LeftUp_Curve_Accept_OtherContext(CPoint point);
	int			ShowCurveInfo(CDrCurve* pDrCurve, char* buf, int jStart);
	//////////////////
	int			LeftDown_PATCH();
	int			LeftUp_EXTRUDE_PAT(POINT point);
	int			LeftUp_ROTATE_PAT(POINT point);
	int			LeftUp_DUCT_PAT(POINT point);
	int			LeftUp_SWEEP_PAT(POINT point);
	int			LeftUp_COONS_PAT(POINT point);
	/////////////////////////////////////////// 
	int			ProcessPatTwist_DUCT_SWEEP();
	int			ProcessPatScale_SWEEP();
	///////////////////////////////////////////
	int			LeftUp_LOFT_PAT(POINT point);
	///
	int			IsEndCondNeeded_LOFT(BOOL& bEndCondMode,
						int& nEndTanNeeded_U,int& nEndTanNeeded_V);
	int			GetBlendInfo_LOFT();
	///////////////////////////////////////////
	int			LeftUp_TENSOR_PAT(POINT point);
	///
	int			TENSORTwistDlgUpdate_PAT();
	int			TENSOREndDlgUpdate_PAT();
	int			IsEndCondNeeded_TENSOR(BOOL& bEndCondMode,
						int& nEndTanNeeded_U,int& nEndTanNeeded_V);
	int			GetBlendInfo_TENSOR();
	int			SwitchToEndCondDlg();
	int			UpdateEndDlg_TRUE();
	int			UpdateEndDlg_FALSE();
	int			UpdateTwistDlg_TRUE();
	int			UpdateTwistDlg_FALSE();
	///////////////////////////////////////////
	int			LeftUp_GORDON_PAT(POINT point);
	///
	int			GORDONEndDlgUpdate_PAT();
	int			IsEndCondNeeded_GORDON(BOOL& bEndCondMode,
						CDListMgr* pCurveList_U,CDListMgr* pCurveList_V);
	int			GetBlendInfo_GORDON();
	int			CheckCompatibility_GORDON_Curve(
						CDListMgr* pCurveList_U,CList<CURVELATCH,CURVELATCH>* pLatchList_U,
						CDListMgr* pCurveList_V,CList<CURVELATCH,CURVELATCH>* pLatchList_V);
	///////////////////////////////////////////
	int			CheckCompatibility_COONS_Curve(CDrCurve* pDrCurve,CURVELATCH& NewLat);
	//////
	int			ProcessPatRotAxis();
	int			UpdatePDlg_TRUE();
	int			UpdatePDlg_FALSE();
	int			UpdatePDlg_FALSE_EXTRUDE();
	int			UpdatePDlg_FALSE_ROTATE();
	int			UpdatePDlg_FALSE_LOFT();
	int			UpdatePDlg_FALSE_TENSOR();
	int			UpdatePDlg_FALSE_GORDON();
	int			UpdatePDlg_FALSE_COONS();
	int			UpdatePDlg_FALSE_DUCT();
	int			UpdatePDlg_FALSE_SWEEP();
	/////////////////////////////////////////////////////////
	int 		PutEndIdsInPlateList(CString nid[],int nEnds);
	int 		PutObjectinPatch(CDrObject* pAddObject,CString nid[],int nEnds);
	//////////////////////////////////////////////////
	int			ShowPatchInfo(CDrPatch* pDrPatch);
	//////////////////////////////////////////////////
	BOOL		IsEndCondNeeded();		// get BlendingInfo & Decide for EndCond


protected:  
// Attributes


	int						m_nExtruType;
											// 1 = Given: Extrusion Direction Nodes
											// 2 = Given: 3 Lenths (wLen) to Extrude to
	BOOL					m_bGenCur;
	CSheet_PATI*			m_pPatInSheet;                                                                                
//	CDlg_PatI*				m_pPatInDlg;                                                                                
	/////////////////////////////////////////// MousePost:MeshGeneration
//	CMI_Pat_P				m_MI_Pat_P;
	/////////////////////////////////////////// MouseInsert:Interpolate
	CMI_Pat_I				m_MI_Pat_I;
	/////////////////////////////////////////// Patch
	CDrPatch*				m_pCurrentPatch;
	CDrCurve*				m_pCurPatCurve;
	CDrCurve*				m_pOldPatCurve;
	CDrCurve*				m_pBlendCurve; // for LoftX
	//////////
	CDListMgr				m_CurveList;		// 
	CList<CURVELATCH,CURVELATCH>	m_LatchList;	
//	CDListMgr				m_NodeList;			// already in CurMouse
//	CList<int,int>			m_ElSegList			// already in CurMouse
	//////////
    int						m_LastPatchNum;		// internal
	PATSUBTYPE				m_PatSubType;
	CString					m_CurrentPatchID;
	CString					m_CurrentPatchIDOld;
	BOOL					m_bPatchDone;		// for dragging
	int						m_nCurveDone;
	int						m_nInfoDone;
	//////////////////////////////// Dlg_PatI
	PATCHPROC				m_PatProc;
	CString					m_Orient;
	WORLD					m_wLen;				
	double					m_dLen;
	//
	BOOL					m_bTwist;		// TRUE=Twist/FALSE=Scale
	////////////////////////////////////
	int						m_nTwistType;
	pDOUBLE					m_pTwist;		// Distrib,if nTwistType = 1
	int						m_nMaxTwist;
	//
	CList<double,double>	m_TwistList;	// Distrib,if nTwistType = 1
	BOOL					m_bIncrement;
	double					m_TwistStart;
	double					m_TwistMult;
	/////////////////////////////////////
	int						m_nScaleType;
	pDOUBLE					m_pScale;		// Distrib,if nTwistType = 1
	int						m_nMaxScale;
	//
	CList<double,double>	m_ScaleList;	// Distrib,if nTwistType = 1
	BOOL					m_bIncScale;
	double					m_ScaleStart;
	double					m_ScaleMult;
	/////////////////////////////////////// Tensor
//	int						m_ElPerSeg; already in Curve
	int						m_ElPerSeg_V;
	int						m_nLastElems_U;	// if Closed
	int						m_nLastElems_V;	// if Closed
	BOOL					m_nNodeDone_U;
	int						m_nNodes_U;
	int						m_nNodes_V;
	CDrCurve*				m_pBlendCurve_U; 
	CDrCurve*				m_pBlendCurve_V;
	int						m_nBlendOrder_U;
	int						m_nBlendOrder_V;
	/////////////
	CList<int,int>			m_ElSegList_U;
	double					m_Ratio_U;
	///
	CList<BLENDEND,BLENDEND>
							m_EndList_U;	// if(bClosed_U or Linear_U,Circle_U,
											// parabola_U) EndList_U Empty
	/////////////
	CList<int,int>			m_ElSegList_V;
	double					m_Ratio_V;
	CList<BLENDEND,BLENDEND>
							m_EndList_V;	// if(bClosed_V or Linear_V,Circle_V,
											// parabola_V) EndList_V Empty
	/////////////
	BOOL					m_bAllSame;			// Dlg_PI_EndCond
	BOOL					m_bEditMode;		// TRUE:User Checking/FALSE:DataInputting
	BOOL					m_bAdvanced;	// yes:end condition needed
	BOOL					m_bEndCondMode;	// end condition needed
	int						m_nEndCondDone;
	int						m_nEndTanNeeded_U;
	int						m_nEndTanNeeded_V;
	BOOL					m_bU;				// TRUE:U_Dir/FALSE:V_Dir
	int						m_indexNode_I;		// Selected BndryNodeIndex in NodeList	
	//////////////////////////////////
	int						m_nTwistDone;
	BOOL					m_bCornerMode;			// needed for Twist
	int						m_nCornerI;
	int						m_nCornerJ;
	PWMAT2					m_pCornerTwist;// it is full,if TW_USER
	TWIST					m_TwistMethod;
	/////////////////////////////////////// Gordon
	BOOL					m_nCurveDone_U;
	int						m_nCurves_U;
	int						m_nCurves_V;
	CDListMgr				m_CurveList_U;		// 
	CList<CURVELATCH,CURVELATCH>	m_LatchList_U;	
	CDListMgr				m_CurveList_V;		// 
	CList<CURVELATCH,CURVELATCH>	m_LatchList_V;	


//Operations
public:

	~CPatMouse();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CPatMouse)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
