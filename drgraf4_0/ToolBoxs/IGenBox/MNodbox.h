// Curvebox.h : header file
// 
#ifndef _MNODBOX_H
#define _MNODBOX_H 


#include "BoxWnd.h"		// BaseClass
#include "MNodBar.h"   //access to CMNodBar
/////////////////////////////////////////////////////////////////////////////
// CMNodBox window

class CMNodBox : public CBoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CMNodBox();
	virtual ~CMNodBox(); 


	DECLARE_DYNAMIC(CMNodBox);



	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CMNodBar*		GetElemBar(){return &m_wndElemBar;};

// Suppations
public:

// Implementation

protected:
    
	///////////////////////////////////////////////////////// children
  	CMNodBar		m_wndElemBar; 


	// Generated message map functions
protected:

	//{{AFX_MSG(CMNodBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

