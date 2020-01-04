#ifndef _CNODESHEET_H
#define _CNODESHEET_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CurSheet.h : header file
//


#include "NodeSheet.h"
#include <afxdlgs.h>

/////////////////////////////////////////////////////////////////////////////
// CCNodeSheet

class CCNodeSheet : public CNodeSheet
{
	DECLARE_DYNAMIC(CCNodeSheet)

// Construction
public:
	CCNodeSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CCNodeSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CCNodeSheet();

// Attributes
public:

// Operations
public:
	virtual int	UpdateSheet(CString& strItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCNodeSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCNodeSheet();

protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CCNodeSheet)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif   // _NODSHEET_H