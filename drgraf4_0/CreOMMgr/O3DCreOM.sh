 // ELMouse.h : header file
//
#ifndef _M3DCREOM_H 
#define _M3DCREOM_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


                    
#include "SolCreOM.h"
#include "DrProf_M.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CO3DCreOM : public CSolCreOM
{
public:

	CO3DCreOM();
//////////////////////////////////////
	DECLARE_SERIAL(CO3DCreOM)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	UINT			ReSetToolID_O3D(UINT CntlID,UINT IGenID, UINT OperID);
	///////////////////////////////////////////////////////////////////////////
	long			CreateorActivateCreOp_O3D(UINT wParam, long lParam);
	long			CancelCreOp_O3D(UINT wParam, long lParam);
	long			GoodByeCreOp_O3D(UINT wParam, long lParam);
	/////////////////////
	void 			OnEBoxMouseMove_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonDown_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonDown_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxLButtonUp_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
	void 			OnEBoxRButtonUp_O3D(CClientDC* pdc,CView* pView,GENERATE gener,
											UINT nFlags, CPoint point);
    ////////////////////////////////////////////////////////////////////// SOLCH

	
protected:


	void		Init_O3D();
	void		Terminate_O3D(BOOL bError);
	//////////////////////////////////////////////
	void		ElementLeftDown_O3D();				// described in derived also
	void		ElementLeftUp_O3D(CPoint point);	// described in derived also
	int			LeftUp_Mbj3D_Accept(CPoint point);
	int			ShowParentMbj3DInfo(CDrMbj3D* pDrMbj3D);
	//////////////////////////////////////////////////////// Mbj3D
	int			LeftUp_GetMbj3D_Parent(POINT point);
	//////////////////////////////////////////////////////// Translate
	int			LeftUp_TRANSLATE_O3D(POINT point);
	//////////////////////////////////////////////////////// Rotate
	int			LeftUp_ROTATE_O3D(POINT point);
	//////////////////////////////////////////////////////// Scale
	int			LeftUp_SCALE_O3D(POINT point);
	//////////////////////////////////////////////////////// Reflect
	int			LeftUp_REFLECT_O3D(POINT point);
	//////////////////////////////////////////////////////// Shear
	int			LeftUp_SHEAR_O3D(POINT point);
	//////////////////////////////////////////////////////// Spawn
	int			LeftUp_OSPAWN(CPoint point);
	int			ShowMbj3DToSpawn(CDrMbj3D* pParentMbj3D,BOOL bUsingDlg);
	int			ReGen_SpawnedMbj3DControls(CDrMbj3D* pSpawnedMbj3D);
	//////////////////////////////////////////////////////// Stitch
	int			LeftUp_OSTITCH(CPoint point);
	BOOL		IsInvalidSplicing(CDrMbj3D* pDrMbj3D);
	int			Update_Status_MSTITCH();
	int			ShowMProfileToStitch();
	int			ShowInputInfo_MSTITCH();
	int			RightUp_NotAutoAccept_MSTITCH();




protected:  
// Attributes


	/////////////////////////////////////////// Mbj3D
	CDrMbj3D*		m_pParentMbj3D;
	CDrMbj3D*		m_pCurrentMbj3D;
	CDrMbj3D*		m_pSpawnedMbj3D;
	/////////////////////////////////////////// STitch
	CDrProf_M*		m_pMProfile;
//	CString			m_ProfileID; same as m_SpawnedID
	CDListMgr		m_Mbj3DList;
	CDListMgr		m_LMList;
	CDrMbj3D*		m_pLastMbj3D;





//Operations
public:

	~CO3DCreOM();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CO3DCreOM)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
