// Patchbox.h : header file
// 
#ifndef _STALBOX_H
#define _STALBOX_H 


#include "BoxWnd.h"		// BaseClass
#include "StaLbar.h"   //access to CPatchBar
/////////////////////////////////////////////////////////////////////////////
// CStaLBox window

class CStaLBox : public CBoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CStaLBox();
	DECLARE_DYNAMIC(CStaLBox);


	virtual ~CStaLBox(); 

	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CStaLBar*		GetElemBar(){return &m_wndElemBar;};
	

// Operations
public:

// Implementation

protected:

    void			ReSetDataDialogs();

	

protected:
    
	
	///////////////////////////////////////////////////////// children
  	CStaLBar	m_wndElemBar; 
    //////////////////////


	// Generated message map functions
protected:

	//{{AFX_MSG(CStaLBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

