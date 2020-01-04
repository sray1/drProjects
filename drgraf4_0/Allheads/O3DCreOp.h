 // ELMouse.h : header file
//
#ifndef _O3DCREOP_H 
#define _O3DCREOP_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


                    
#include "SolCreOp.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CO3DCreOp : public CSolCreOp
{
public:

	CO3DCreOp();
//////////////////////////////////////
	DECLARE_SERIAL(CO3DCreOp)
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
	int			LeftUp_Obj3D_Accept(CPoint point);
	int			ShowParentObj3DInfo(CDrObj3D* pDrObj3D);
	//////////////////////////////////////////////////////// Obj3D
	int			LeftUp_GetObj3D_Parent(POINT point);
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

	int			ShowObj3DToSpawn(CDrObj3D* pParentObj3D,BOOL bUsingDlg);
	int			ReGen_SpawnedObj3DControls(CDrObj3D* pSpawnedObj3D);
	int			ShowObj3DToSpawnCopyOff(CDrObj3D* pParentObj3D,BOOL bUsingDlg);
	int			Obj3DDependent_SpawnConnectedObjects_CopyOff(CDrObj3D* pCurrentObj3D,BOOL bUsingDlg,
																					UINT nObjType);
	int			Obj3DSpawnCopyOff(CDrObj3D* pParentObj3D,BOOL bUsingDlg);


protected:  
// Attributes


	/////////////////////////////////////////// Obj3D
	CDrObj3D*		m_pParentObj3D;
	CDrObj3D*		m_pCurrentObj3D;
	CDrObj3D*		m_pSpawnedObj3D;


//Operations
public:

	~CO3DCreOp();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CO3DCreOp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
