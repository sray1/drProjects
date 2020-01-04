// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__B72ECA36_51F5_11D2_8A0E_00A0CC30503B__INCLUDED_)
#define AFX_MAINFRM_H__B72ECA36_51F5_11D2_8A0E_00A0CC30503B__INCLUDED_

#include "MySlider.h"
#include "MyButton.h"
#include "AnimButton.h"


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void		AnimateBitMap_Horizontal(); 
	void		MoveBitMap(); 

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

	CMyButton	m_MyButton;
	CAnimButton	m_AnimBut;

	CMySlider	m_wndHSlider,m_wndVSlider;
	int			m_HSliderPos,m_VSliderPos;
	int			m_HSliderOldPos,m_VSliderOldPos;

	int			m_HSliderSavePos,m_VSliderSavePos;   // debugging purposes

	BOOL		m_bFirst;     // want to avoid restoring old bitmap on 1st call
						     //  to OnPaint

	CBitmap		m_BMSave, m_BMSrc;

//	CMyBitmapButton	m_wndBmButton;


// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg long OnOpenFrame(UINT wParam, UINT lParam);
	afx_msg long OnAnimateBM(UINT wParam, UINT lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__B72ECA36_51F5_11D2_8A0E_00A0CC30503B__INCLUDED_)
