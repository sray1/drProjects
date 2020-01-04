// Elembox.h : header file
// 
#ifndef _IGENBOX_H
#define _IGENBOX_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

#include "BoxWnd.h"		// BaseClass
#include "IGenBar.h"   //access to CElemBar
#include "NodeBox.h"   //access to CNodeBox
#include "CurveBox.h"   //access to CCurveBox
#include "PatchBox.h"   //access to CPatchBox
#include "SolidBox.h"   //access to CSolidBox
/////////////////////////////////////////////////////////////////////////////
// CIGenBox window

class CIGenBox : public CBoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CIGenBox();
	virtual ~CIGenBox(); 


	DECLARE_DYNAMIC(CIGenBox);



	BOOL			Create(CWnd* pParentWnd,CRect rect);
	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
	///////////////////////////////////////////////////////////
	BOOL 			CreateElemBar();
	CIGenBar*		GetElemBar(){return &m_wndElemBar;};
	////////////////////////////////////////////////////////////// NodeBoxes
    CNodeBox* 		GetNodeBox(){return &m_wndNodeBox;};
    CSize			GetSizeNodeBox(){return m_szNodeBox;};
    void			SetSizeNodeBox(CSize szBox){m_szNodeBox = szBox;};
	////////////////////////////////////////////////////////////// CurveBoxes
    CCurveBox* 		GetCurveBox(){return &m_wndCurveBox;};
    CSize			GetSizeCurveBox(){return m_szCurveBox;};
    void			SetSizeCurveBox(CSize szBox){m_szCurveBox = szBox;};
	////////////////////////////////////////////////////////////// PatchBoxes
    CPatchBox* 		GetPatchBox(){return &m_wndPatchBox;};
    CSize			GetSizePatchBox(){return m_szPatchBox;};
    void			SetSizePatchBox(CSize szBox){m_szPatchBox = szBox;};
	////////////////////////////////////////////////////////////// SolidBoxes
    CSolidBox* 		GetSolidBox(){return &m_wndSolidBox;};
    CSize			GetSizeSolidBox(){return m_szSolidBox;};
    void			SetSizeSolidBox(CSize szBox){m_szSolidBox = szBox;};


// Operations
public:

// Implementation

protected:
    
	//////////////////////////////// children
  	CIGenBar	m_wndElemBar; 
	//////////////////////////////// NodeBox
	CNodeBox	m_wndNodeBox;
	CSize		m_szNodeBox;
	//////////////////////////////// CurveBox
	CCurveBox	m_wndCurveBox;
	CSize		m_szCurveBox;
	//////////////////////////////// PatchBox
	CPatchBox	m_wndPatchBox;
	CSize		m_szPatchBox;
	//////////////////////////////// SolidBox
	CSolidBox	m_wndSolidBox;
	CSize		m_szSolidBox;
    ////////////////////////


    //////////////////////
	// Generated message map functions
protected:

	//{{AFX_MSG(CIGenBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif

