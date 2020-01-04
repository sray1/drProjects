 // ELMouse.h : header file
//
#ifndef _PATMDIT_H 
#define _PATMDIT_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>			// CList Template
                    
#include "CurMdit.h"
/////////////////////
#include "DrMesh2D.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CPatMdit : public CCurMdit
{
public:

	CPatMdit();
//////////////////////////////////////
	DECLARE_SERIAL(CPatMdit)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	///////////////////////////////////////////////////////////////////////////
	UINT			ReSetToolID_PAT(UINT CntlID,UINT IGenID, UINT OperID);
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
 	///////////////////////////////////////////////////// NODE
	int				ShowPatchToEdit(CDrMesh2D* pDrPatch);
	int				ShowPatchInfo(CDrMesh2D* pDrPatch);
		
protected:


	//////////////////////////////////////////////
	void		ElementLeftDown_PAT();				// described in derived also
	void		ElementLeftUp_PAT(CPoint point);	// described in derived also
	int			LeftUp_Patch(CPoint point);


protected:  
// Attributes


 	/////////////////////////////////////////// Patch
	CDrMesh2D*	m_pCurrentPatch;

	
	
//Operations
public:

	~CPatMdit();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CPatMdit)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
