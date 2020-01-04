 // ELMouse.h : header file
//
#ifndef _CURCREOP_H 
#define _CURCREOP_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


                    
#include "NodCreOp.h"
#include "DrProf_C.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CCurCreOp : public CNodCreOp
{
public:

	CCurCreOp();
//////////////////////////////////////
	DECLARE_SERIAL(CCurCreOp)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	UINT			ReSetToolID_CUR(UINT CntlID,UINT IGenID, UINT OperID);
	///////////////////////////////////////////////////////////////////////////
	long			CreateorActivateCreOp_CUR(UINT wParam, long lParam);
	long			CancelCreOp_CUR(UINT wParam, long lParam);
	long			GoodByeCreOp_CUR(UINT wParam, long lParam);
	/////////////////////
	void 			OnEBoxMouseMove_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonDown_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonUp_CUR(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
    ////////////////////////////////////////////////////////////////////// PATCH

	
protected:


	void		Init_CUR();
	void		Terminate_CUR(BOOL bError);
	//////////////////////////////////////////////
	void		ElementLeftDown_CUR();				// described in derived also
	void		ElementLeftUp_CUR(CPoint point);	// described in derived also
	int			LeftUp_Curve_Accept(CPoint point);
	int			ShowParentCurveInfo(CDrCurve* pDrCurve);
	//////////////////////////////////////////////////////// Patch
	int			LeftUp_GetCurve_Parent(POINT point);
	//////////////////////////////////////////////////////// Translate
	int			LeftUp_TRANSLATE_CUR(POINT point);
	//////////////////////////////////////////////////////// Rotate
	int			LeftUp_ROTATE_CUR(POINT point);
	//////////////////////////////////////////////////////// Scale
	int			LeftUp_SCALE_CUR(POINT point);
	//////////////////////////////////////////////////////// Reflect
	int			LeftUp_REFLECT_CUR(POINT point);
	//////////////////////////////////////////////////////// Shear
	int			LeftUp_SHEAR_CUR(POINT point);
	//////////////////////////////////////////////////////// Spawn
	int			LeftUp_CSPAWN(CPoint point);
	int			ShowCurveToSpawn(CDrCurve* pParentCurve,BOOL bUsingDlg);
	int			ReGen_SpawnedCurveControls(CDrCurve* pSpawnedCurve);
	int			ShowCurveToSpawnCopyOff(CDrCurve* pParentCurve,BOOL bUsingDlg);
	int			CurveDependent_SpawnConnectedObjects_CopyOff(CDrCurve* pCurrentCurve,BOOL bUsingDlg,
																					UINT nObjType);
	int			CurveSpawnCopyOff(CDrCurve* pParentCurve,BOOL bUsingDlg);
	//////////////////////////////////////////////////////// Stitch
	int			LeftUp_CSTITCH(CPoint point);
	int			CloneCurvesForPrivateListofCProf(CDrProf_C* pCProfile,CDListMgr* pCurveList);
	BOOL		IsInvalidSplicing(CDrCurve* pDrCurve);
	int			ShowCProfileToStitch();
	int			RightUp_NotAutoAccept_CSTITCH();
	int			ShowInputInfo_CSTITCH();
	int			Update_Status_CSTITCH();
	///////////////////////////////////////////////////////// Blend
	int			LeftUp_CBLEND(CPoint point);
	int			Get_N_FillBlendInfo(CDListMgr* pBCurList,CDListMgr* pCurList);
	CDrCurve*	TempInDataBase_BlendCurve(CString* pID);
	int			SetOtherInfo_BlendCubic(CDrCurve* pCurve,CDrCurve* pCurveL,CDrCurve* pCurveR);
	int			CreateTemp_BlendCurve(CDrCurve* pCurve);
	int			RightUp_NotAutoAccept_CBLEND();
	int			ShowInputInfo_CBLEND();
	int			Update_Status_CBLEND();



protected:  
// Attributes


	BOOL			m_bBlend;
	BOOL			m_bStitch;
	/////////////////////////////////////////// Curve
	CDrCurve*		m_pParentCurve;
	CDrCurve*		m_pCurrentCurve;
	/////////////////////////////////////////// Blend
	CDListMgr		m_BCurveList;
	/////////////////////////////////////////// STitch
	CDrProf_C*		m_pCProfile;
//	CString			m_ProfileID; same as m_SpawnedID
	CDListMgr		m_CurveList;
	CDListMgr		m_LMList;
	CDrCurve*		m_pLastCurve;

//Operations
public:

	~CCurCreOp();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CCurCreOp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
