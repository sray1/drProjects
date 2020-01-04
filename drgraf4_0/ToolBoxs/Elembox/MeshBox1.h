// Elembox.h : header file
// 
#ifndef _MESHBOX1_H
#define _MESHBOX1_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA
#include "EoxWnd.h"		// BaseClass
#include "MeshBar1.h"   //access to CMeshBar
#include "PipeBox.h"   //access to CPipeBox
//#include "BeamBox.h"   //access to CBeamBox
//#include "TrussBox.h"   //access to CTrussBox
/////////////////////////////////////////////////////////////////////////////
// CMeshBox1 window

class CMeshBox1 : public CEoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CMeshBox1();
	virtual ~CMeshBox1(); 


	DECLARE_DYNAMIC(CMeshBox1);



 	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
	///////////////////////////////////////////////////////////
	BOOL 			CreateElemBar();
	CMeshBar1*		GetElemBar(){return &m_wndElemBar;};
	////////////////////////////////////////////////////////////// TriBoxes
    CPipeBox* 		GetPipeBox(){return &m_wndPipeBox;};
    CSize			GetSizePipeBox(){return m_szPipeBox;};
    void			SetSizePipeBox(CSize szBox){m_szPipeBox = szBox;};
/*
	////////////////////////////////////////////////////////////// BeamBoxes
    CBeamBox* 		GetBeamBox(){return &m_wndBeamBox;};
    CSize			GetSizeBeamBox(){return m_szBeamBox;};
    void			SetSizeBeamBox(CSize szBox){m_szBeamBox = szBox;};
	////////////////////////////////////////////////////////////// TriBoxes
    CTrussBox* 		GetTrussBox(){return &m_wndTrussBox;};
    CSize			GetSizeTrussBox(){return m_szTrussBox;};
    void			SetSizeTrussBox(CSize szBox){m_szTrussBox = szBox;};
*/


// Operations
public:

// Implementation

protected:
    
	//////////////////////////////// children
  	CMeshBar1	m_wndElemBar; 
	//////////////////////////////// PipeBox
	CPipeBox	m_wndPipeBox;
	CSize		m_szPipeBox;
/*
	//////////////////////////////// BeamBox
	CBeamBox	m_wndBeamBox;
	CSize		m_szBeamBox;
	//////////////////////////////// TrussBox
	CTrussBox	m_wndTrussBox;
	CSize		m_szTrussBox;
*/
	
	// Generated message map functions
protected:

	//{{AFX_MSG(CMeshBox1)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif

