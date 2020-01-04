
#ifndef _ANIMBUTTON_H
#define _ANIMBUTTON_H


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MyButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAnimButton window

class CAnimButton : public CButton
{
// Construction
public:
	CAnimButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimButton)
	public:
	virtual BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );


	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAnimButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAnimButton)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClicked();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif //
