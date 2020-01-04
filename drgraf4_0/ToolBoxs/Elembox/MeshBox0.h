// Elembox.h : header file
// 
#ifndef _MESHBOX0_H
#define _MESHBOX0_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA
#include "EoxWnd.h"		// BaseClass
#include "MeshBar0.h"   //access to CMeshBar
/////////////////////////////////////////////////////////////////////////////
// CMeshBox0 window

class CMeshBox0 : public CEoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CMeshBox0();
	virtual ~CMeshBox0(); 


	DECLARE_DYNAMIC(CMeshBox0);


 	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
	///////////////////////////////////////////////////////////
	BOOL 			CreateElemBar();
	CMeshBar0*		GetElemBar(){return &m_wndElemBar;};



// Operations
public:

// Implementation

protected:
    
	//////////////////////////////// children
  	CMeshBar0	m_wndElemBar; 

	
	// Generated message map functions
protected:

	//{{AFX_MSG(CMeshBox0)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif

