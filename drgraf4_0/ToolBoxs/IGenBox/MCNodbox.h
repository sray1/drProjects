// Curvebox.h : header file
// 
#ifndef _MCNODBOX_H
#define _MCNODBOX_H 


#include "BoxWnd.h"		// BaseClass
#include "MCNodBar.h"   //access to CMNodBar
/////////////////////////////////////////////////////////////////////////////
// CMCNodBox window

class CMCNodBox : public CBoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CMCNodBox();
	virtual ~CMCNodBox(); 


	DECLARE_DYNAMIC(CMCNodBox);



	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CMCNodBar*		GetElemBar(){return &m_wndElemBar;};

// Suppations
public:

// Implementation

protected:
    
	///////////////////////////////////////////////////////// children
  	CMCNodBar		m_wndElemBar; 


	// Generated message map functions
protected:

	//{{AFX_MSG(CMCNodBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

