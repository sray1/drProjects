// Hexbox.h : header file
// 
#ifndef _HEXBOX_H
#define _HEXBOX_H 


#include "EoxWnd.h"		// BaseClass
#include "Hexbar.h"   //access to CCurveBar
/////////////////////////////////////////////////////////////////////////////
// CHexBox window

class CHexBox : public CEoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CHexBox();
	virtual ~CHexBox(); 


	DECLARE_DYNAMIC(CHexBox);



    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CHexBar*		GetElemBar(){return &m_wndElemBar;};
	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members

// Operations
public:

// Implementation

protected:
    
	///////////////////////////////////////////////////////// children
  	CHexBar		m_wndElemBar; 


	// Generated message map functions
protected:

	//{{AFX_MSG(CHexBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

