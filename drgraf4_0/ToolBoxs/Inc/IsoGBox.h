// Elembox.h : header file
// 
#ifndef _ISOGBOX_H
#define _ISOGBOX_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

#include "BoxWnd.h"		// BaseClass
#include "CntlBar.h"   //access to CElemBar
#include "INodBox.h"   //access to CNodeBox
#include "ICurBox.h"   //access to CCurveBox
#include "IPatBox.h"   //access to CPatchBox
#include "ISolBox.h"   //access to CSolidBox
/////////////////////////////////////////////////////////////////////////////
// CIsoGBox window

class CIsoGBox : public CBoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CIsoGBox();
	virtual ~CIsoGBox(); 


	DECLARE_DYNAMIC(CIsoGBox);



 	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CCntlBar*		GetElemBar(){return &m_wndElemBar;};
	////////////////////////////////////////////////////////////// NodeBoxes
    CINodBox* 		GetNodeBox(){return &m_wndNodeBox;};
    CSize			GetSizeNodeBox(){return m_szNodeBox;};
    void			SetSizeNodeBox(CSize szBox){m_szNodeBox = szBox;};
	////////////////////////////////////////////////////////////// CurveBoxes
    CICurBox* 		GetCurveBox(){return &m_wndCurveBox;};
    CSize			GetSizeCurveBox(){return m_szCurveBox;};
    void			SetSizeCurveBox(CSize szBox){m_szCurveBox = szBox;};
	////////////////////////////////////////////////////////////// PatchBoxes
    CIPatBox* 		GetPatchBox(){return &m_wndPatchBox;};
    CSize			GetSizePatchBox(){return m_szPatchBox;};
    void			SetSizePatchBox(CSize szBox){m_szPatchBox = szBox;};
	////////////////////////////////////////////////////////////// SolidBoxes
    CISolBox* 		GetSolidBox(){return &m_wndSolidBox;};
    CSize			GetSizeSolidBox(){return m_szSolidBox;};
    void			SetSizeSolidBox(CSize szBox){m_szSolidBox = szBox;};


// Operations
public:

// Implementation

protected:
    
	///////////////////////////////////////////////////////// children
  	CCntlBar	m_wndElemBar; 
	//////////////////////////////// NodeBox
	CINodBox	m_wndNodeBox;
	CSize		m_szNodeBox;
	//////////////////////////////// CurveBox
	CICurBox	m_wndCurveBox;
	CSize		m_szCurveBox;
	//////////////////////////////// PatchBox
	CIPatBox	m_wndPatchBox;
	CSize		m_szPatchBox;
	//////////////////////////////// SolidBox
	CISolBox	m_wndSolidBox;
	CSize		m_szSolidBox;


    //////////////////////
	// Generated message map functions
protected:

	//{{AFX_MSG(CIsoGBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif

