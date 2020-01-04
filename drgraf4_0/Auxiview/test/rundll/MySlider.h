#if !defined(AFX_MYSLIDER_H__E0BB2580_56BB_11D2_8A0E_00A0CC30503B__INCLUDED_)
#define AFX_MYSLIDER_H__E0BB2580_56BB_11D2_8A0E_00A0CC30503B__INCLUDED_



#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MySlider.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMySlider window

class CMySlider : public CSliderCtrl
{
// Construction
public:
	CMySlider();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySlider)
	public:
	virtual BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );


	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMySlider();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMySlider)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSLIDER_H__E0BB2580_56BB_11D2_8A0E_00A0CC30503B__INCLUDED_)
