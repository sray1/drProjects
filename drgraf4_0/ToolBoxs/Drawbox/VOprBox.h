// Elembox.h : header file
// 
#ifndef _VOPRBOX_H
#define _VOPRBOX_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

#include "BoxWnd.h"		// BaseClass
#include "VOprBar.h"   //access to CElemBar
/////////////////////////////////////////////////////////////////////////////
// CVOprBox window

class CVOprBox : public CBoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CVOprBox();
	virtual ~CVOprBox(); 


	DECLARE_DYNAMIC(CVOprBox);



	BOOL			Create(CWnd* pParentWnd,CRect rect);
	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
	///////////////////////////////////////////////////////////
	BOOL 			CreateElemBar();
	CVOprBar*		GetElemBar(){return &m_wndElemBar;};


// Operations
public:

// Implementation

protected:
    
	//////////////////////////////// children
  	CVOprBar	m_wndElemBar; 
    ////////////////////////


    //////////////////////
	// Generated message map functions
protected:

	//{{AFX_MSG(CVOprBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif

