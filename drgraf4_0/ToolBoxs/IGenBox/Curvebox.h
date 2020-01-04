// Curvebox.h : header file
// 
#ifndef _CURVEBOX_H
#define _CURVEBOX_H 


#include "BoxWnd.h"		// BaseClass
#include "CurveBar.h"   //access to CCurveBar
/////////////////////////////////////////////////////////////////////////////
// CCurveBox window

class CCurveBox : public CBoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CCurveBox();
	virtual ~CCurveBox(); 


	DECLARE_DYNAMIC(CCurveBox);



	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CCurveBar*		GetElemBar(){return &m_wndElemBar;};


// Operations
public:

// Implementation

protected:
    
	///////////////////////////////////////////////////////// children
  	CCurveBar	m_wndElemBar; 


	// Generated message map functions
protected:

	//{{AFX_MSG(CCurveBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

