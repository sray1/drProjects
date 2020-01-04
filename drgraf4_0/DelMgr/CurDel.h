 // ELMouse.h : header file
//
#ifndef _CURDEL_H 
#define _CURDEL_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "NodDel.h"
/////////////////////
#include "DrCurve.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CCurDel : public CNodDel
{
public:

	CCurDel();
//////////////////////////////////////
	DECLARE_SERIAL(CCurDel)
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
	int				ShowCurveToDelete(CDrCurve* pDrCurve, BOOL bToBeDeleted);
	int				MarkCurve_Delete(CDrCurve* pDrCurve);
	int				ShowCurveInfo(CDrCurve* pDrCurve);
				
		

protected:


	//////////////////////////////////////////////
	void			ElementLeftDown_CUR();				// described in derived also
	void			ElementLeftUp_CUR(CPoint point);	// described in derived also
	int				LeftUp_CURVE(CPoint point);


protected:  
// Attributes


 	/////////////////////////////////////////// Curve
	CDrCurve*	m_pCurrentCurve;



//Operations
public:

	~CCurDel();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CCurDel)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
