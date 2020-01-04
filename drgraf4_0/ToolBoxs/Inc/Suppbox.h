// Patchbox.h : header file
// 
#ifndef _SUPPBOX_H
#define _SUPPBOX_H 


#include "BoxWnd.h"		// BaseClass
#include "Suppbar.h"   //access to CPatchBar
/////////////////////////////////////////////////////////////////////////////
// CSuppBox window

class CSuppBox : public CBoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CSuppBox();
	DECLARE_DYNAMIC(CSuppBox);


	virtual ~CSuppBox(); 

	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CSuppBar*		GetElemBar(){return &m_wndElemBar;};
	///////////////////////////////////
	

// Operations
public:

// Implementation

protected:

    void			ReSetDataDialogs();

	
protected:

	///////////////////////////////////////////////////////// children
  	CSuppBar	m_wndElemBar; 
    //////////////////////


	// Generated message map functions
protected:

	//{{AFX_MSG(CSuppBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

