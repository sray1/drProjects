#if !defined(AFX_SUPPSHEET_H__F121307F_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_SUPPSHEET_H__F121307F_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SuppSheet.h : header file
//


#include "DrPropSheet.h"
#include "SuppDefnPage.h"
#include "SuppInputPage.h"
#include "SuppDebugPage.h"
/////////////////////////////////////////////////////////////////////////////
// CSuppSheet

class CSuppSheet : public CDrPropSheet
{
	DECLARE_DYNAMIC(CSuppSheet)

// Construction
public:
	CSuppSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSuppSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:
	virtual int	UpdateSheet(CString& strItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuppSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSuppSheet();

protected:
	CSuppDefnPage*		m_pSuppDefnPage;
	CSuppInputPage*		m_pSuppInputPage;
	CSuppDebugPage*		m_pSuppDebugPage;

	// Generated message map functions
protected:
	//{{AFX_MSG(CSuppSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPPSHEET_H__F121307F_72EF_11D2_8B46_444553540000__INCLUDED_)
