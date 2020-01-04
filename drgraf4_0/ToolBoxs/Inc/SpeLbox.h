// Patchbox.h : header file
// 
#ifndef _SPELBOX_H
#define _SPELBOX_H 


#include "BoxWnd.h"		// BaseClass
#include "SpeLbar.h"   //access to CPatchBar
/////////////////////////////////////////////////////////////////////////////
// CSpeLBox window

class CSpeLBox : public CBoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CSpeLBox();
	DECLARE_DYNAMIC(CSpeLBox);


	virtual ~CSpeLBox(); 

	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CSpeLBar*		GetElemBar(){return &m_wndElemBar;};
	///////////////////////////////////////////////////////////
	

// Operations
public:

// Implementation

protected:

    void			ReSetDataDialogs();

	

protected:
    
	
	///////////////////////////////////////////////////////// children
  	CSpeLBar	m_wndElemBar; 
    //////////////////////


	// Generated message map functions
protected:

	//{{AFX_MSG(CSpeLBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

