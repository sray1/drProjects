// Patchbox.h : header file
// 
#ifndef _COPBOX_H
#define _COPBOX_H 


#include "BoxWnd.h"		// BaseClass
#include "COpBar.h"   //access to CPatchBar
/////////////////////////////////////////////////////////////////////////////
// CCOpBox window

class CCOpBox : public CBoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CCOpBox();
	DECLARE_DYNAMIC(CCOpBox);


	virtual ~CCOpBox(); 

	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CCOpBar*		GetElemBar(){return &m_wndElemBar;};
	///////////////////////////////////
	

// Operations
public:

// Implementation

protected:
    
	
	///////////////////////////////////////////////////////// children
  	CCOpBar			m_wndElemBar; 
    //////////////////////


	// Generated message map functions
protected:

	//{{AFX_MSG(CCOpBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

