// Hexbox.h : header file
// 
#ifndef _PIPEBOX_H
#define _PIPEBOX_H 


#include "EoxWnd.h"		// BaseClass
#include "PipeBar.h"   //access to CCurveBar
/////////////////////////////////////////////////////////////////////////////
// CPipeBox window

class CPipeBox : public CEoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CPipeBox();
	virtual ~CPipeBox(); 


	DECLARE_DYNAMIC(CPipeBox);



	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CPipeBar*		GetElemBar(){return &m_wndElemBar;};

// Operations
public:

// Implementation

protected:
    
	///////////////////////////////////////////////////////// children
  	CPipeBar		m_wndElemBar; 


	// Generated message map functions
protected:

	//{{AFX_MSG(CPipeBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

