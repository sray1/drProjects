// Tetbox.h : header file
// 
#ifndef _TETBOX_H
#define _TETBOX_H 


#include "EoxWnd.h"		// BaseClass
#include "Tetbar.h"   //access to CCurveBar
/////////////////////////////////////////////////////////////////////////////
// CTetBox window

class CTetBox : public CEoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CTetBox();
	virtual ~CTetBox(); 


	DECLARE_DYNAMIC(CTetBox);



	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CTetBar*		GetElemBar(){return &m_wndElemBar;};

// Operations
public:

// Implementation

protected:
    
	///////////////////////////////////////////////////////// children
  	CTetBar		m_wndElemBar; 


	// Generated message map functions
protected:

	//{{AFX_MSG(CTetBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

