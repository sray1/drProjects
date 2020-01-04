// Patchbox.h : header file
// 
#ifndef _PATCHBOX_H
#define _PATCHBOX_H 


#include "BoxWnd.h"		// BaseClass
#include "PatchBar.h"   //access to CPatchBar
/////////////////////////////////////////////////////////////////////////////
// CPatchBox window

class CPatchBox : public CBoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CPatchBox();
	virtual ~CPatchBox(); 


	DECLARE_DYNAMIC(CPatchBox);



	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CPatchBar*		GetElemBar(){return &m_wndElemBar;};


// Operations
public:

// Implementation

protected:
    
	///////////////////////////////////////////////////////// children
  	CPatchBar	m_wndElemBar; 


	// Generated message map functions
protected:

	//{{AFX_MSG(CPatchBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

