// Tribox.h : header file
// 
#ifndef _TRIBOX_H
#define _TRIBOX_H 


#include "EoxWnd.h"		// BaseClass
#include "Tribar.h"   //access to CCurveBar
/////////////////////////////////////////////////////////////////////////////
// CTriBox window

class CTriBox : public CEoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CTriBox();
	virtual ~CTriBox(); 


	DECLARE_DYNAMIC(CTriBox);



 	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
   /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CTriBar*		GetElemBar(){return &m_wndElemBar;};

// Operations
public:

// Implementation

protected:
    
	///////////////////////////////////////////////////////// children
  	CTriBar		m_wndElemBar; 


	// Generated message map functions
protected:

	//{{AFX_MSG(CTriBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

