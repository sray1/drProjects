#if !defined(AFX_SOLIDSHEET_H__F1213078_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_SOLIDSHEET_H__F1213078_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SolidSheet.h : header file
//


#include "DrPropSheet.h"
#include "SolidGeomPage.h"
#include "SolidInputPage.h"
#include "SolidLoadPage.h"
#include "SolidSuppPage.h"
#include "SolidRestPage.h"
#include "SolidDebugPage.h"
/////////////////////////////////////////////////////////////////////////////
// CSolidSheet

class CSolidSheet : public CDrPropSheet
{
	DECLARE_DYNAMIC(CSolidSheet)

// Construction
public:
	CSolidSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSolidSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:
	virtual int	UpdateSheet(CString& strItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSolidSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSolidSheet();

protected:
	CSolidGeomPage*		m_pSolidGeomPage;
	CSolidInputPage*	m_pSolidInputPage;
	CSolidLoadPage*		m_pSolidLoadPage;
	CSolidRestPage*		m_pSolidRestPage;
	CSolidSuppPage*		m_pSolidSuppPage;
	CSolidDebugPage*	m_pSolidDebugPage;

	// Generated message map functions
protected:
	//{{AFX_MSG(CSolidSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOLIDSHEET_H__F1213078_72EF_11D2_8B46_444553540000__INCLUDED_)
