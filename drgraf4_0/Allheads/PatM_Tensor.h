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
//	CDlg_PatI*		GetActivePatPage(){return m_pPatInDlg;};                                                                                
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
	void		ResetVariables();
	int			Terminate_PAT(BOOL bError);
	int			RightUp_Premature_PAT();
	int			RightUp_NotAutoAccept_PAT();
	int			ShowPatch(CString* pID);
	//////////////////////////////////////////////
	void		ElementLeftDown_PAT();				// described in derived also
	void		ElementLeftUp_PAT(CPoint point);	// described in derived also
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
	int			LeftUp_LOFT_PAT(POINT point);
	int			LeftUp_DUCT_PAT(POINT point);
	int			LeftUp_SWEEP_PAT(POINT point);
	int			LeftUp_COONS_PAT(POINT point);
	int			LeftUp_TENSOR_PAT(POINT point);
	int			LeftUp_GORDON_PAT(POINT point);
	int			CheckCompatibility_COONS_Curve(CDrCurve* pDrCurve,CURVELATCH& NewLat);
	void		UpdatePDlg_TRUE();
	void		UpdatePDlg_FALSE();
	/////////////////////////////////////////////////////////
	int 		PutEndIdsInPlateList(CString nid[],int nEnds);
	int 		PutObjectinPatch(CDrObject* pAddObject,CString nid[],int nEnds);
	//////////////////////////////////////////////////
	int				ShowPatchInfo(CDrPatch* pDrPatch);
/*
	//////////////////////////////////////////////////////// Spawn
//	Moved to CreOMgr Dll   01/14/98 
	int				LeftUp_PSPAWN(CPoint point);
	int				ShowPatchToSpawn(CDrPatch* pDrPatch);
//	Moved to CreOMgr Dll   01/14/98 end
*/


protected:  
// Attributes


//	CDlg_PatI*				m_pPatInDlg;                                                                                
	CSheet_PATI*			m_pPatSheet;                                                                                
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
	double					m_dLen;				// also Angle for Rotation
	BOOL					m_bTwist;
	BOOL					m_bIncrement;
	double					m_TwistStart;
	double					m_TwistMult;
	BOOL					m_bIncRad;
	double					m_RadStart;
	double					m_RadiusMult;
	/////////////////////////////////////// Tensor
	BOOL					m_nNodeDone_U;
	int						m_nNodes_U;
	int						m_nNodes_V;
	CDrCurve*				m_pBlendCurve_U; 
	CDrCurve*				m_pBlendCurve_V;
	/////////////
	pWORLD					m_CornerTwist[2][2];// it is full,if TW_USER
	TWIST					m_TwistMethod;
	/////////////
	CList<int,int>			m_ElSegList_U;
	double					m_Ratio_U;
	CList<BLENDEND,BLENDEND>
							m_EndList_U;	// if(bClosed_U or Linear_U,Circle_U,
											// parabola_U) EndList_U Empty
	/////////////
	CList<int,int>			m_ElSegList_V;
	double					m_Ratio_V;
	CList<BLENDEND,BLENDEND>
							m_EndList_V;	// if(bClosed_V or Linear_V,Circle_V,
											// parabola_V) EndList_V Empty
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
