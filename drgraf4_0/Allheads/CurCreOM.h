 // ELMouse.h : header file
//
#ifndef _CURCREOM_H 
#define _CURCREOM_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


                    
#include "NodCreOM.h"
#include "DrMesh1D.h"
#include "DrProf_1.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CCurCreOM : public CNodCreOM
{
public:

	CCurCreOM();
//////////////////////////////////////
	DECLARE_SERIAL(CCurCreOM)
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
	int			ShowParentCurveInfo(CDrMesh1D* pDrCurve);
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
	int			ShowCurveToSpawn(CDrMesh1D* pParentCurve,BOOL bUsingDlg);
	int			ShowCurveToSpawnCopyOff(CDrMesh1D* pParentCurve,BOOL bUsingDlg);
	int			CurveDependent_SpawnConnectedObjects_CopyOff(CDrMesh1D* pCurrentCurve,BOOL bUsingDlg,
																					UINT nObjType);
	int			CurveSpawnCopyOff(CDrMesh1D* pParentCurve,BOOL bUsingDlg);
	//////////////////////////////////////////////////////// Stitch
	int			LeftUp_CSTITCH(CPoint point);
	BOOL		IsInvalidSplicing(CDrMesh1D* pDrCurve);
	int			ShowCProfileToStitch();
	int			RightUp_NotAutoAccept_STITCH();
	int			ShowInputInfo_STITCH();
	int			Update_Status_CSTITCH();
	/////////////////////////////////////////////////////////



protected:  
// Attributes


	BOOL			m_bStitch;
	/////////////////////////////////////////// Curve
	CDrMesh1D*		m_pParentCurve;
	CDrMesh1D*		m_pCurrentCurve;
	/////////////////////////////////////////// STitch
	CDrProf_1*		m_pCProfile;
//	CString			m_ProfileID; same as m_SpawnedID
	CDListMgr		m_CurveList;
	CDListMgr		m_LMList;
	CDrMesh1D*		m_pLastCurve;

//Operations
public:

	~CCurCreOM();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CCurCreOM)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
