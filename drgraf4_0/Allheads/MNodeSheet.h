#ifndef _MNODESHEET_H
#define _MNODESHEET_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CurSheet.h : header file
//


#include "NodeSheet.h"
#include <afxdlgs.h>

/////////////////////////////////////////////////////////////////////////////
// CMNodeSheet

class CMNodeSheet : public CNodeSheet
{
	DECLARE_DYNAMIC(CMNodeSheet)

// Construction
public:
	CMNodeSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMNodeSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMNodeSheet();

// Attributes
public:

// Operations
public:
	virtual int	UpdateSheet(CString& strItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMNodeSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMNodeSheet();

protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMNodeSheet)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif   // _NODSHEET_H