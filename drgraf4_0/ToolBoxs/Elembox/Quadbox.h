// Quadbox.h : header file
// 
#ifndef _QUADBOX_H
#define _QUADBOX_H 


#include "EoxWnd.h"		// BaseClass
#include "Quadbar.h"   //access to CCurveBar
/////////////////////////////////////////////////////////////////////////////
// CQuadBox window

class CQuadBox : public CEoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CQuadBox();
	virtual ~CQuadBox(); 


	DECLARE_DYNAMIC(CQuadBox);



	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CQuadBar*		GetElemBar(){return &m_wndElemBar;};

// Operations
public:
	BOOL 			IsEditMoveTool(UINT nID);

// Implementation

protected:
    
	///////////////////////////////////////////////////////// children
  	CQuadBar		m_wndElemBar; 


	// Generated message map functions
protected:

	//{{AFX_MSG(CQuadBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

