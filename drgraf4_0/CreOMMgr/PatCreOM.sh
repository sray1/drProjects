 // ELMouse.h : header file
//
#ifndef _MS2CREOM_H 
#define _MS2CREOM_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


                    
#include "CurCreOM.h"
#include "DrProf_2.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CMs2CreOM : public CMs1CreOM
{
public:

	CMs2CreOM();
//////////////////////////////////////
	DECLARE_SERIAL(CMs2CreOM)
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
	int			LeftUp_Mesh2D_Accept(CPoint point);
	int			ShowParentMesh2DInfo(CDrMesh2D* pDrMesh2D);
	//////////////////////////////////////////////////////// Mesh2D
	int			LeftUp_GetMesh2D_Parent(POINT point);
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
	int			ShowMesh2DToSpawn(CDrMesh2D* pParentMesh2D,BOOL bUsingDlg);
	int			ReGen_SpawnedMesh2DControls(CDrMesh2D* pSpawnedMesh2D);
	//////////////////////////////////////////////////////// Stitch
	int			LeftUp_PSTITCH(CPoint point);
	BOOL		IsInvalidSplicing(CDrMesh2D* pDrMesh2D);
	int			Update_Status_2STITCH();
	int			Show2ProfileToStitch();
	int			ShowInputInfo_2STITCH();
	int			RightUp_NotAutoAccept_2STITCH();




protected:  
// Attributes


	/////////////////////////////////////////// Mesh2D
	CDrMesh2D*		m_pParentMesh2D;
	CDrMesh2D*		m_pCurrentMesh2D;
	CDrMesh2D*		m_pSpawnedMesh2D;
	/////////////////////////////////////////// STitch
	CDrProf_2*		m_p2Profile;
//	CString			m_ProfileID; same as m_SpawnedID
	CDListMgr		m_Mesh2DList;
	CDListMgr		m_LMList;
	CDrMesh2D*		m_pLastMesh2D;





//Operations
public:

	~CMs2CreOM();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMs2CreOM)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
