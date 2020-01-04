// Elembox.h : header file
// 
#ifndef _CNTLBOX_H
#define _CNTLBOX_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

#include "BoxWnd.h"		// BaseClass
#include "CntlBar.h"   //access to CCntlBar
#include "SuppBox.h"   //access to CSuppBox
#include "StaLBox.h"   //access to CStaLBox
#include "DynLBox.h"   //access to CDynLBox
#include "SpeLBox.h"   //access to CSpeLBox
/////////////////////////////////////////////////////////////////////////////
// CCntlBox window

class CCntlBox : public CBoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CCntlBox();
	virtual ~CCntlBox(); 


	DECLARE_DYNAMIC(CCntlBox);



	BOOL			Create(CWnd* pParentWnd,CRect rect);
	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CCntlBar*		GetElemBar(){return &m_wndElemBar;};
	////////////////////////////////////////////////////////////// SuppBoxes
    CSuppBox* 		GetSuppBox(){return &m_wndSuppBox;};
    CSize			GetSizeSuppBox(){return m_szSuppBox;};
    void			SetSizeSuppBox(CSize szBox){m_szSuppBox = szBox;};
	////////////////////////////////////////////////////////////// StaticLoadBox
    CStaLBox* 		GetStaLBox(){return &m_wndStaLBox;};
    CSize			GetSizeStaLBox(){return m_szStaLBox;};
    void			SetSizeStaLBox(CSize szBox){m_szStaLBox = szBox;};
	////////////////////////////////////////////////////////////// HistoryLoadBox
    CDynLBox* 		GetDynLBox(){return &m_wndDynLBox;};
    CSize			GetSizeDynLBox(){return m_szDynLBox;};
    void			SetSizeDynLBox(CSize szBox){m_szDynLBox = szBox;};
	////////////////////////////////////////////////////////////// SPectraLoadBox
    CSpeLBox* 		GetSpeLBox(){return &m_wndSpeLBox;};
    CSize			GetSizeSpeLBox(){return m_szSpeLBox;};
    void			SetSizeSpeLBox(CSize szBox){m_szSpeLBox = szBox;};


// Operations
public:

// Implementation

protected:
    
	//////////////////////////////// ModelBox
  	CCntlBar	m_wndElemBar; 
	//////////////////////////////// SuppBox
	CSuppBox	m_wndSuppBox;
	CSize		m_szSuppBox;
	//////////////////////////////// StaLBox
	CStaLBox	m_wndStaLBox;
	CSize		m_szStaLBox;
	//////////////////////////////// DynLBox
	CDynLBox	m_wndDynLBox;
	CSize		m_szDynLBox;
	//////////////////////////////// SpeLBox
	CSpeLBox	m_wndSpeLBox;
	CSize		m_szSpeLBox;


    //////////////////////
	// Generated message map functions
protected:

	//{{AFX_MSG(CCntlBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif

