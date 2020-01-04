 // ELMouse.h : header file
//
#ifndef _MS1CREOM_H 
#define _MS1CREOM_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


                    
#include "NodCreOM.h"
#include "DrProf_1.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CMs1CreOM : public CMs0CreOM
{
public:

	CMs1CreOM();
//////////////////////////////////////
	DECLARE_SERIAL(CMs1CreOM)
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
	int			LeftUp_MESH1D_Accept(CPoint point);
	int			ShowParentMESH1DInfo(CDrMesh1D* pDrMESH1D);
	//////////////////////////////////////////////////////// Patch
	int			LeftUp_GetMESH1D_Parent(POINT point);
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
	int			ShowMESH1DToSpawn(CDrMesh1D* pParentMESH1D,BOOL bUsingDlg);
	int			ReGen_SpawnedMESH1DControls(CDrMesh1D* pSpawnedMESH1D);
	//////////////////////////////////////////////////////// Stitch
	int			LeftUp_CSTITCH(CPoint point);
	BOOL		IsInvalidSplicing(CDrMesh1D* pDrMESH1D);
	int			Show1ProfileToStitch();
	int			RightUp_NotAutoAccept_1STITCH();
	int			ShowInputInfo_1STITCH();
	int			Update_Status_1STITCH();



protected:  
// Attributes


	/////////////////////////////////////////// MESH1D
	CDrMesh1D*		m_pParentMESH1D;
	CDrMesh1D*		m_pCurrentMESH1D;
	CDrMesh1D*		m_pSpawnedMESH1D;
	/////////////////////////////////////////// STitch
	CDrProf_1*		m_p1Profile;
//	CString			m_ProfileID; same as m_SpawnedID
	CDListMgr		m_Mesh1DList;
	CDListMgr		m_LMList;
	CDrMesh1D*		m_pLastMESH1D;

//Operations
public:

	~CMs1CreOM();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMs1CreOM)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
