#ifndef _CURVESHEET_H
#define _CURVESHEET_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CurSheet.h : header file
//


#include "DrPropSheet.h"
#include "CurveGeomPage.h"
#include "CurveInputPage.h"
#include "CurveLoadPage.h"
#include "CurveSuppPage.h"
#include "CurveRestPage.h"
#include "CurveDebugPage.h"
#include <afxdlgs.h>

/////////////////////////////////////////////////////////////////////////////
// CCurveSheet

class CCurveSheet : public CDrPropSheet
{
	DECLARE_DYNAMIC(CCurveSheet)

// Construction
public:
	CCurveSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CCurveSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CCurveSheet();

// Attributes
public:

// Operations
public:
	virtual int	UpdateSheet(CString& strItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurveSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCurveSheet();

protected:
	CCurveGeomPage*		m_pCurveGeomPage;
	CCurveInputPage*	m_pCurveInputPage;
	CCurveLoadPage*		m_pCurveLoadPage;
	CCurveRestPage*		m_pCurveRestPage;
	CCurveSuppPage*		m_pCurveSuppPage;
	CCurveDebugPage*	m_pCurveDebugPage;

	// Generated message map functions
protected:
	//{{AFX_MSG(CCurveSheet)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif   // _NODSHEET_H