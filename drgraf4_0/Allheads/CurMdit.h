 // ELMouse.h : header file
//
#ifndef _CURMDIT_H 
#define _CURMDIT_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include <afxtempl.h>			// CList Template

#include "NodMdit.h"
/////////////////////
#include "DrMesh1D.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CCurMdit : public CNodMdit
{
public:

	CCurMdit();
//////////////////////////////////////
	DECLARE_SERIAL(CCurMdit)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

	///////////////////////////////////////////////////////////////////////////
	UINT			ReSetToolID_CUR(UINT CntlID,UINT IGenID, UINT OperID);
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
 	///////////////////////////////////////////////////// NODE
	int				ShowCurveToEdit(CDrMesh1D* pDrCurve);
	int				ShowCurveInfo(CDrMesh1D* pDrCurve);
				
		

protected:


	//////////////////////////////////////////////
	void			ElementLeftDown_CUR();				// described in derived also
	void			ElementLeftUp_CUR(CPoint point);	// described in derived also
	int				LeftUp_CURVE(CPoint point);


protected:  
// Attributes


 	/////////////////////////////////////////// Curve
	CDrMesh1D*	m_pCurrentCurve;



//Operations
public:

	~CCurMdit();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CCurMdit)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
