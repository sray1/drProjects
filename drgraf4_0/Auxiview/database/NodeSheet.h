#ifndef _NODESHEET_H
#define _NODESHEET_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CurSheet.h : header file
//


#include "NodeGeomPage.h"
#include "NodeInputPage.h"
#include "NodeLoadPage.h"
#include "NodeDispPage.h"
#include "NodeSuppPage.h"
#include "NodeRestPage.h"
#include "NodeDebugPage.h"
#include <afxdlgs.h>

/////////////////////////////////////////////////////////////////////////////
// CNodeSheet

class CNodeSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CNodeSheet)

// Construction
public:
	CNodeSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CNodeSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CNodeSheet();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNodeSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNodeSheet();

protected:
	CNodeGeomPage*	m_pNodeGeomPage;
	CNodeInputPage* m_pNodeInputPage;
	CNodeLoadPage*	m_pNodeLoadPage;
	CNodeDispPage*	m_pNodeDispPage;
	CNodeRestPage*	m_pNodeRestPage;
	CNodeSuppPage*	m_pNodeSuppPage;
	CNodeDebugPage* m_pNodeDebugPage;

	// Generated message map functions
protected:
	//{{AFX_MSG(CNodeSheet)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif   // _NODSHEET_H