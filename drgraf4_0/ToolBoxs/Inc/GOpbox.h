// Patchbox.h : header file
// 
#ifndef _GOPBOX_H
#define _GOPBOX_H 


#include "BoxWnd.h"		// BaseClass
#include "GOpBar.h"   //access to CPatchBar
/////////////////////////////////////////////////////////////////////////////
// CGOpBox window

class CGOpBox : public CBoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CGOpBox();
	DECLARE_DYNAMIC(CGOpBox);


	virtual ~CGOpBox(); 

	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CGOpBar*		GetElemBar(){return &m_wndElemBar;};
	///////////////////////////////////
	

// Operations
public:

// Implementation

protected:
    
	
	///////////////////////////////////////////////////////// children
  	CGOpBar			m_wndElemBar; 
    //////////////////////


	// Generated message map functions
protected:

	//{{AFX_MSG(CGOpBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

