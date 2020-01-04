 // ELMouse.h : header file
//
#ifndef _PATDEL_H 
#define _PATDEL_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "CurDel.h"
/////////////////////
#include "DrPatch.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CPatDel : public CCurDel
{
public:

	CPatDel();
//////////////////////////////////////
	DECLARE_SERIAL(CPatDel)
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
	int				ShowPatchToDelete(CDrPatch* pDrPatch, BOOL bToBeDeleted);
	int				MarkPatch_Delete(CDrPatch* pDrPatch);
	int				ShowPatchInfo(CDrPatch* pDrPatch);
		
protected:


	//////////////////////////////////////////////
	void		ElementLeftDown_PAT();				// described in derived also
	void		ElementLeftUp_PAT(CPoint point);	// described in derived also
	int			LeftUp_Patch(CPoint point);


protected:  
// Attributes


 	/////////////////////////////////////////// Patch
	CDrPatch*	m_pCurrentPatch;

	
	
//Operations
public:

	~CPatDel();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CPatDel)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
