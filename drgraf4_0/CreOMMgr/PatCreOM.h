 // ELMouse.h : header file
//
#ifndef _PATCREOM_H 
#define _PATCREOM_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


                    
#include "CurCreOM.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CPatCreOM : public CCurCreOM
{
public:

	CPatCreOM();
//////////////////////////////////////
	DECLARE_SERIAL(CPatCreOM)
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
	int			ShowParentPatchInfo(CDrMesh2D* pDrPatch);
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
	int			ShowPatchToSpawn(CDrMesh2D* pParentPatch,BOOL bUsingDlg);
	int			ReGen_SpawnedPatchControls(CDrMesh2D* pSpawnedPatch);
	int			ShowPatchToSpawnCopyOff(CDrMesh2D* pParentPatch,BOOL bUsingDlg);
	int			PatchDependent_SpawnConnectedObjects_CopyOff(CDrMesh2D* pCurrentPatch,BOOL bUsingDlg,
																					UINT nObjType);
	int			PatchSpawnCopyOff(CDrMesh2D* pParentPatch,BOOL bUsingDlg);


protected:  
// Attributes


	/////////////////////////////////////////// Patch
	CDrMesh2D*		m_pParentPatch;
	CDrMesh2D*		m_pCurrentPatch;
	CDrMesh2D*		m_pSpawnedPatch;


//Operations
public:

	~CPatCreOM();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CPatCreOM)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
