// Elembox.h : header file
// 
#ifndef _MESHBOX2_H
#define _MESHBOX2_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA
#include "EoxWnd.h"		// BaseClass
#include "MeshBar2.h"   //access to CMeshBar
#include "TriBox.h"		//access to CCTriBox
#include "QuadBox.h"	//access to CQuadBox
/////////////////////////////////////////////////////////////////////////////
// CMeshBox2 window

class CMeshBox2 : public CEoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CMeshBox2();
	virtual ~CMeshBox2(); 


	DECLARE_DYNAMIC(CMeshBox2);



 	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
	///////////////////////////////////////////////////////////
	BOOL 			CreateElemBar();
	CMeshBar2*		GetElemBar(){return &m_wndElemBar;};
	////////////////////////////////////////////////////////////// TriBoxes
    CTriBox* 		GetTriBox(){return &m_wndTriBox;};
    CSize			GetSizeTriBox(){return m_szTriBox;};
    void			SetSizeTriBox(CSize szBox){m_szTriBox = szBox;};
	////////////////////////////////////////////////////////////// QuadBoxes
    CQuadBox* 		GetQuadBox(){return &m_wndQuadBox;};
    CSize			GetSizeQuadBox(){return m_szQuadBox;};
    void			SetSizeQuadBox(CSize szBox){m_szQuadBox = szBox;};



// Operations
public:

// Implementation

protected:
    
	//////////////////////////////// children
  	CMeshBar2	m_wndElemBar; 
	//////////////////////////////// TriBox
	CTriBox		m_wndTriBox;
	CSize		m_szTriBox;
	//////////////////////////////// QuadBox
	CQuadBox	m_wndQuadBox;
	CSize		m_szQuadBox;
    //////////////////////

	
	// Generated message map functions
protected:

	//{{AFX_MSG(CMeshBox2)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif

