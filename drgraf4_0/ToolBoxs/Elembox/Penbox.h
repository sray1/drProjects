// Curvebox.h : header file
// 
#ifndef _PENBOX_H
#define _PENBOX_H 


#include "EoxWnd.h"		// BaseClass
#include "Penbar.h"   //access to CCurveBar
/////////////////////////////////////////////////////////////////////////////
// CPenBox window

class CPenBox : public CEoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CPenBox();
	virtual ~CPenBox(); 


	DECLARE_DYNAMIC(CPenBox);



	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CPenBar*		GetElemBar(){return &m_wndElemBar;};

// Operations
public:

// Implementation

protected:
    
	///////////////////////////////////////////////////////// children
  	CPenBar		m_wndElemBar; 


	// Generated message map functions
protected:

	//{{AFX_MSG(CPenBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

