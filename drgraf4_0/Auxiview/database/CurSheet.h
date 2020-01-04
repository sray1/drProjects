
#ifndef _CURSHEET_H
#define _CURSHEET_H


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CurSheet.h : header file
//

#include "CurGeomPage.h"
#include "CurIntPage.h"
#include <afxdlgs.h>

/////////////////////////////////////////////////////////////////////////////
// CCurSheet

class CCurSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CCurSheet)

// Construction
public:
	CCurSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CCurSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CCurSheet();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCurSheet();

protected:
	CCurGeomPage*	m_pCurGeomPage;
	CCurIntPage*	m_pCurIntPage;

	// Generated message map functions
protected:
	//{{AFX_MSG(CCurSheet)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif		// _CURSHEET_H

