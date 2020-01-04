// Elembox.h : header file
// 
#ifndef _MGENBOX_H
#define _MGENBOX_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

#include "BoxWnd.h"		// BaseClass
#include "IGenBar.h"   //access to CElemBar
#include "MNodBox.h"   //access to CMNodBox
#include "MCNodBox.h"   //access to CMCNodBox
/////////////////////////////////////////////////////////////////////////////
// CMGenBox window

class CMGenBox : public CBoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CMGenBox();
	virtual ~CMGenBox(); 


	DECLARE_DYNAMIC(CMGenBox);



	BOOL			Create(CWnd* pParentWnd,CRect rect);
	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
	///////////////////////////////////////////////////////////
	BOOL 			CreateElemBar();
	CIGenBar*		GetElemBar(){return &m_wndElemBar;};
	////////////////////////////////////////////////////////////// NodeBoxes
    CMNodBox* 		GetNodeBox(){return &m_wndNodeBox;};
    CSize			GetSizeNodeBox(){return m_szNodeBox;};
    void			SetSizeNodeBox(CSize szBox){m_szNodeBox = szBox;};
	////////////////////////////////////////////////////////////// NodeBoxes
    CMCNodBox* 		GetCNodeBox(){return &m_wndCNodeBox;};
    CSize			GetSizeCNodeBox(){return m_szCNodeBox;};
    void			SetSizeCNodeBox(CSize szBox){m_szCNodeBox = szBox;};


// Operations
public:

// Implementation

protected:
    
	//////////////////////////////// children
  	CIGenBar	m_wndElemBar; 
	//////////////////////////////// NodeBox
	CMNodBox	m_wndNodeBox;
	CSize		m_szNodeBox;
	//////////////////////////////// NodeBox
	CMCNodBox	m_wndCNodeBox;
	CSize		m_szCNodeBox;
    ////////////////////////


    //////////////////////
	// Generated message map functions
protected:

	//{{AFX_MSG(CMGenBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif

