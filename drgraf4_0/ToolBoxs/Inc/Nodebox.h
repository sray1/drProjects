// Curvebox.h : header file
// 
#ifndef _NODEBOX_H
#define _NODEBOX_H 


#include "BoxWnd.h"		// BaseClass
#include "NodeBar.h"   //access to CNodeBar
/////////////////////////////////////////////////////////////////////////////
// CNodeBox window

class CNodeBox : public CBoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CNodeBox();
	virtual ~CNodeBox(); 


	DECLARE_DYNAMIC(CNodeBox);



	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CNodeBar*		GetElemBar(){return &m_wndElemBar;};

// Suppations
public:

// Implementation

protected:
    
	///////////////////////////////////////////////////////// children
  	CNodeBar		m_wndElemBar; 


	// Generated message map functions
protected:

	//{{AFX_MSG(CNodeBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

