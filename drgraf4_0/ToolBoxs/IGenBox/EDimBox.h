// Patchbox.h : header file
// 
#ifndef _EDIMBOX_H
#define _EDIMBOX_H 


#include "BoxWnd.h"		// BaseClass
#include "EDimBar.h"   //access to CEDimBar
#include "MeshBox0.h"   //access to CMeshBox0
#include "MeshBox1.h"   //access to CMeshBox0
#include "MeshBox2.h"   //access to CMeshBox0
#include "MeshBox3.h"   //access to CMeshBox0
/////////////////////////////////////////////////////////////////////////////
// CEDimBox window

class CEDimBox : public CBoxWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CEDimBox();
	virtual ~CEDimBox(); 

	
	DECLARE_DYNAMIC(CEDimBox);



	BOOL			Create(CWnd* pParentWnd,CRect rect);
	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CEDimBar*		GetElemBar(){return &m_wndElemBar;};
	////////////////////////////////////////////////////////////// MeshBoxes
    CMeshBox0* 		GetMeshBox0(){return &m_wndMeshBox0;};
    CSize			GetSizeMeshBox0(){return m_szMeshBox0;};
    void			SetSizeMeshBox0(CSize szBox){m_szMeshBox0 = szBox;};
	////////////////////////////////////////////////////////////// MeshBoxes
    CMeshBox1* 		GetMeshBox1(){return &m_wndMeshBox1;};
    CSize			GetSizeMeshBox1(){return m_szMeshBox1;};
    void			SetSizeMeshBox1(CSize szBox){m_szMeshBox1 = szBox;};
	////////////////////////////////////////////////////////////// MeshBoxes
    CMeshBox2* 		GetMeshBox2(){return &m_wndMeshBox2;};
    CSize			GetSizeMeshBox2(){return m_szMeshBox2;};
    void			SetSizeMeshBox2(CSize szBox){m_szMeshBox2 = szBox;};
	////////////////////////////////////////////////////////////// MeshBoxes
    CMeshBox3* 		GetMeshBox3(){return &m_wndMeshBox3;};
    CSize			GetSizeMeshBox3(){return m_szMeshBox3;};
    void			SetSizeMeshBox3(CSize szBox){m_szMeshBox3 = szBox;};
	

// Operations
public:

// Implementation


protected:

    
	
	///////////////////////////////////////////////////////// children
  	CEDimBar	m_wndElemBar; 
	//////////////////////////////// MeshBox
	CMeshBox0	m_wndMeshBox0;
	CSize		m_szMeshBox0;
	//////////////////////////////// MeshBox
	CMeshBox1	m_wndMeshBox1;
	CSize		m_szMeshBox1;
	//////////////////////////////// MeshBox
	CMeshBox2	m_wndMeshBox2;
	CSize		m_szMeshBox2;
	//////////////////////////////// MeshBox
	CMeshBox3	m_wndMeshBox3;
	CSize		m_szMeshBox3;


	// Generated message map functions
protected:

	//{{AFX_MSG(CEDimBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};
/////////////////////////////////////////////////////////////////////////////
#endif

