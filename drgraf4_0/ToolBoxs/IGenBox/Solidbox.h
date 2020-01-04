// Solidbox.h : header file
// 
#ifndef _SOLIDBOX_H
#define _SOLIDBOX_H 


#include "BoxWnd.h"		// BaseClass
#include "SolidBar.h"   //access to CSolidBar
/////////////////////////////////////////////////////////////////////////////
// CSolidBox window

class CSolidBox : public CBoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CSolidBox();
	virtual ~CSolidBox(); 

	
	DECLARE_DYNAMIC(CSolidBox);



	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CSolidBar*		GetElemBar(){return &m_wndElemBar;};


// Operations
public:

// Implementation

protected:
    
	///////////////////////////////////////////////////////// children
  	CSolidBar	m_wndElemBar; 



	// Generated message map functions
protected:

	//{{AFX_MSG(CSolidBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

