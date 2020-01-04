#ifndef _MCNODESHEET_H
#define _MCNODESHEET_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CurSheet.h : header file
//


#include "NodeSheet.h"
#include <afxdlgs.h>

/////////////////////////////////////////////////////////////////////////////
// CMCNodeSheet

class CMCNodeSheet : public CNodeSheet
{
	DECLARE_DYNAMIC(CMCNodeSheet)

// Construction
public:
	CMCNodeSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMCNodeSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMCNodeSheet();

// Attributes
public:

// Operations
public:
	virtual int	UpdateSheet(CString& strItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMCNodeSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMCNodeSheet();

protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMCNodeSheet)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif   // _NODSHEET_H