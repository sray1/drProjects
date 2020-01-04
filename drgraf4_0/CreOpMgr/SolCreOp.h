 // ELMouse.h : header file
//
#ifndef _SOLCREOP_H 
#define _SOLCREOP_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


                    
#include "PatCreOp.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CSolCreOp : public CPatCreOp
{
public:

	CSolCreOp();
//////////////////////////////////////
	DECLARE_SERIAL(CSolCreOp)
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
	int			ShowParentSolidInfo(CDrSolid* pDrSolid);
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

	int			ShowSolidToSpawn(CDrSolid* pParentSolid,BOOL bUsingDlg);
	int			ReGen_SpawnedSolidControls(CDrSolid* pSpawnedSolid);
	int			ShowSolidToSpawnCopyOff(CDrSolid* pParentSolid,BOOL bUsingDlg);
	int			SolidDependent_SpawnConnectedObjects_CopyOff(CDrSolid* pCurrentSolid,BOOL bUsingDlg,
																					UINT nObjType);
	int			SolidSpawnCopyOff(CDrSolid* pParentSolid,BOOL bUsingDlg);


protected:  
// Attributes


	/////////////////////////////////////////// Solid
	CDrSolid*		m_pParentSolid;
	CDrSolid*		m_pCurrentSolid;
	CDrSolid*		m_pSpawnedSolid;


//Operations
public:

	~CSolCreOp();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CSolCreOp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
