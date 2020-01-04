// Elembox.h : header file
// 
#ifndef _MAINBOX_H
#define _MAINBOX_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

#include "BoxWnd.h"		// BaseClass
#include "MainBar.h"   //access to CElemBar
#include "GOpBox.h"   //access to GOpBox
#include "COpBox.h"   //access to COpBox
/////////////////////////////////////////////////////////////////////////////
// CMainBox window

class CMainBox : public CBoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CMainBox();
	virtual ~CMainBox(); 


	DECLARE_DYNAMIC(CMainBox);



	BOOL			Create(CWnd* pParentWnd,CRect rect);
	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
	///////////////////////////////////////////////////////////
	BOOL 			CreateElemBar();
	CMainBar*		GetElemBar(){return &m_wndElemBar;};
	////////////////////////////////////////////////////////////// CreateOpsBoxes
    CCOpBox* 		GetCOpBox(){return &m_wndCOpBox;};
    CSize			GetSizeCOpBox(){return m_szCOpBox;};
    void			SetSizeCOpBox(CSize szBox){m_szCOpBox = szBox;};
	////////////////////////////////////////////////////////////// GenOpsBoxes
    CGOpBox* 		GetGOpBox(){return &m_wndGOpBox;};
    CSize			GetSizeGOpBox(){return m_szGOpBox;};
    void			SetSizeGOpBox(CSize szBox){m_szGOpBox = szBox;};
	////////////////////////////////////////////////////////////// BullOpsBoxes
	////////////////////////////////////////////////////////////// FEMOpsBoxes


// Operations
public:

// Implementation

protected:
    
	//////////////////////////////// children
  	CMainBar	m_wndElemBar; 
	//////////////////////////////// NodeBox
	CCOpBox		m_wndCOpBox;
	CSize		m_szCOpBox;
	//////////////////////////////// NodeBox
	CGOpBox		m_wndGOpBox;
	CSize		m_szGOpBox;
    ////////////////////////


    //////////////////////
	// Generated message map functions
protected:

	//{{AFX_MSG(CMainBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif

