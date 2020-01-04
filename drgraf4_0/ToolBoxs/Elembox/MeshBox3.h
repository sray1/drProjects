// Elembox.h : header file
// 
#ifndef _MESHBOX3_H
#define _MESHBOX3_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA
#include "EoxWnd.h"		// BaseClass
#include "MeshBar3.h"   //access to CMeshBar
#include "HexBox.h"		//access to CHexBox
#include "PenBox.h"		//access to CHexBox
#include "TetBox.h"		//access to CHexBox
/////////////////////////////////////////////////////////////////////////////
// CMeshBox3 window

class CMeshBox3 : public CEoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CMeshBox3();
	virtual ~CMeshBox3(); 


	DECLARE_DYNAMIC(CMeshBox3);



 	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
	///////////////////////////////////////////////////////////
	BOOL 			CreateElemBar();
	CMeshBar3*		GetElemBar(){return &m_wndElemBar;};
	////////////////////////////////////////////////////////////// HexBoxes
    CHexBox* 		GetHexBox(){return &m_wndHexBox;};
    CSize			GetSizeHexBox(){return m_szHexBox;};
    void			SetSizeHexBox(CSize szBox){m_szHexBox = szBox;};
	////////////////////////////////////////////////////////////// PenBoxes
    CPenBox* 		GetPenBox(){return &m_wndPenBox;};
    CSize			GetSizePenBox(){return m_szPenBox;};
    void			SetSizePenBox(CSize szBox){m_szPenBox = szBox;};
	////////////////////////////////////////////////////////////// TetBoxes
    CTetBox* 		GetTetBox(){return &m_wndTetBox;};
    CSize			GetSizeTetBox(){return m_szTetBox;};
    void			SetSizeTetBox(CSize szBox){m_szTetBox = szBox;};



// Operations
public:

// Implementation

protected:
    
	//////////////////////////////// children
  	CMeshBar3	m_wndElemBar; 
	//////////////////////////////// HexBox
	CHexBox		m_wndHexBox;
	CSize		m_szHexBox;
	//////////////////////////////// PenBox
	CPenBox		m_wndPenBox;
	CSize		m_szPenBox;
	//////////////////////////////// TetBox
	CTetBox		m_wndTetBox;
	CSize		m_szTetBox;
    //////////////////////

	
	// Generated message map functions
protected:

	//{{AFX_MSG(CMeshBox3)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif

