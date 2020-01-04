 // ELMouse.h : header file
//
#ifndef _PATCREOP_H 
#define _PATCREOP_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


                    
#include "CurCreOp.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CPatCreOp : public CCurCreOp
{
public:

	CPatCreOp();
//////////////////////////////////////
	DECLARE_SERIAL(CPatCreOp)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	UINT			ReSetToolID_PAT(UINT CntlID,UINT IGenID, UINT OperID);
	///////////////////////////////////////////////////////////////////////////
	long			CreateorActivateCreOp_PAT(UINT wParam, long lParam);
	long			CancelCreOp_PAT(UINT wParam, long lParam);
	long			GoodByeCreOp_PAT(UINT wParam, long lParam);
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

	
protected:


	void		Init_PAT();
	void		Terminate_PAT(BOOL bError);
	//////////////////////////////////////////////
	void		ElementLeftDown_PAT();				// described in derived also
	void		ElementLeftUp_PAT(CPoint point);	// described in derived also
	int			LeftUp_Patch_Accept(CPoint point);
	int			ShowParentPatchInfo(CDrPatch* pDrPatch);
	//////////////////////////////////////////////////////// Patch
	int			LeftUp_GetPatch_Parent(POINT point);
	//////////////////////////////////////////////////////// Translate
	int			LeftUp_TRANSLATE_PAT(POINT point);
	//////////////////////////////////////////////////////// Rotate
	int			LeftUp_ROTATE_PAT(POINT point);
	//////////////////////////////////////////////////////// Scale
	int			LeftUp_SCALE_PAT(POINT point);
	//////////////////////////////////////////////////////// Reflect
	int			LeftUp_REFLECT_PAT(POINT point);
	//////////////////////////////////////////////////////// Shear
	int			LeftUp_SHEAR_PAT(POINT point);
	//////////////////////////////////////////////////////// Spawn
	int			LeftUp_PSPAWN(CPoint point);
	int			ShowPatchToSpawn(CDrPatch* pParentPatch,BOOL bUsingDlg);
	int			ReGen_SpawnedPatchControls(CDrPatch* pSpawnedPatch);
	int			ShowPatchToSpawnCopyOff(CDrPatch* pParentPatch,BOOL bUsingDlg);
	int			PatchDependent_SpawnConnectedObjects_CopyOff(CDrPatch* pCurrentPatch,BOOL bUsingDlg,
																					UINT nObjType);
	int			PatchSpawnCopyOff(CDrPatch* pParentPatch,BOOL bUsingDlg);


protected:  
// Attributes


	/////////////////////////////////////////// Patch
	CDrPatch*		m_pParentPatch;
	CDrPatch*		m_pCurrentPatch;
	CDrPatch*		m_pSpawnedPatch;


//Operations
public:

	~CPatCreOp();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CPatCreOp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
