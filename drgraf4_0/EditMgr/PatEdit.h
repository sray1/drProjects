 // ELMouse.h : header file
//
#ifndef _PATEDIT_H 
#define _PATEDIT_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>			// CList Template
                    
#include "CurEdit.h"
/////////////////////
#include "DrPatch.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CPatEdit : public CCurEdit
{
public:

	CPatEdit();
//////////////////////////////////////
	DECLARE_SERIAL(CPatEdit)
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
	int				ShowPatchToEdit(CDrPatch* pDrPatch);
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

	~CPatEdit();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CPatEdit)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
