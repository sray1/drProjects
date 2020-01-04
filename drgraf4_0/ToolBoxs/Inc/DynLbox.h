// Patchbox.h : header file
// 
#ifndef _DYNLBOX_H
#define _DYNLBOX_H 


#include "BoxWnd.h"		// BaseClass
#include "DynLbar.h"   //access to CPatchBar
/////////////////////////////////////////////////////////////////////////////
// CDynLBox window

class CDynLBox : public CBoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CDynLBox();
	DECLARE_DYNAMIC(CDynLBox);


	virtual ~CDynLBox(); 

	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CDynLBar*		GetElemBar(){return &m_wndElemBar;};
	

// Operations
public:

// Implementation

protected:

    void			ReSetDataDialogs();

	

protected:
    
	
	///////////////////////////////////////////////////////// children
  	CDynLBar	m_wndElemBar; 
    //////////////////////


	// Generated message map functions
protected:

	//{{AFX_MSG(CDynLBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

