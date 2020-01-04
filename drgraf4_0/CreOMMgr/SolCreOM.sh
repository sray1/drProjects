 // ELMouse.h : header file
//
#ifndef _MS3CREOM_H 
#define _MS3CREOM_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


                    
#include "PatCreOM.h"
#include "DrProf_3.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CMs3CreOM : public CMs2CreOM
{
public:

	CMs3CreOM();
//////////////////////////////////////
	DECLARE_SERIAL(CMs3CreOM)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	UINT			ReSetToolID_SOL(UINT CntlID,UINT IGenID, UINT OperID);
	///////////////////////////////////////////////////////////////////////////
	long			CreateorActivateCreOp_SOL(UINT wParam, long lParam);
	long			CancelCreOp_SOL(UINT wParam, long lParam);
	long			GoodByeCreOp_SOL(UINT wParam, long lParam);
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
    ////////////////////////////////////////////////////////////////////// SOLCH

	
protected:


	void		Init_SOL();
	void		Terminate_SOL(BOOL bError);
	//////////////////////////////////////////////
	void		ElementLeftDown_SOL();				// described in derived also
	void		ElementLeftUp_SOL(CPoint point);	// described in derived also
	int			LeftUp_Solid_Accept(CPoint point);
	int			ShowParentSolidInfo(CDrMesh3D* pDrMesh3D);
	//////////////////////////////////////////////////////// Solid
	int			LeftUp_GetSolid_Parent(POINT point);
	//////////////////////////////////////////////////////// Translate
	int			LeftUp_TRANSLATE_SOL(POINT point);
	//////////////////////////////////////////////////////// Rotate
	int			LeftUp_ROTATE_SOL(POINT point);
	//////////////////////////////////////////////////////// Scale
	int			LeftUp_SCALE_SOL(POINT point);
	//////////////////////////////////////////////////////// Reflect
	int			LeftUp_REFLECT_SOL(POINT point);
	//////////////////////////////////////////////////////// Shear
	int			LeftUp_SHEAR_SOL(POINT point);
	//////////////////////////////////////////////////////// Spawn
	int			LeftUp_SSPAWN(CPoint point);
	int			ShowMesh3DToSpawn(CDrMesh3D* pParentMesh3D,BOOL bUsingDlg);
	int			ReGen_SpawnedMesh3DControls(CDrMesh3D* pSpawnedMesh3D);
	//////////////////////////////////////////////////////// Stitch
	int			LeftUp_SSTITCH(CPoint point);
	BOOL		IsInvalidSplicing(CDrMesh3D* pDrMESH3D);
	int			Update_Status_3STITCH();
	int			Show3ProfileToStitch();
	int			ShowInputInfo_3STITCH();
	int			RightUp_NotAutoAccept_3STITCH();



protected:  
// Attributes


	/////////////////////////////////////////// Solid
	CDrMesh3D*		m_pParentMesh3D;
	CDrMesh3D*		m_pCurrentMesh3D;
	CDrMesh3D*		m_pSpawnedMesh3D;
	/////////////////////////////////////////// STitch
	CDrProf_3*		m_p3Profile;
//	CString			m_ProfileID; same as m_SpawnedID
	CDListMgr		m_Mesh3DList;
	CDListMgr		m_LMList;
	CDrMesh3D*		m_pLastMesh3D;





//Operations
public:

	~CMs3CreOM();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMs3CreOM)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
