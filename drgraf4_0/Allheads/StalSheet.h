#if !defined(AFX_STALSHEET_H__F1213080_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_STALSHEET_H__F1213080_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StalSheet.h : header file
//


#include "DrPropSheet.h"
#include "StalDefnPage.h"
#include "StalInputPage.h"
#include "StalDebugPage.h"
/////////////////////////////////////////////////////////////////////////////
// CStalSheet

class CStalSheet : public CDrPropSheet
{
	DECLARE_DYNAMIC(CStalSheet)

// Construction
public:
	CStalSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CStalSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:
	virtual int	UpdateSheet(CString& strItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStalSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStalSheet();

protected:
	CStalDefnPage*		m_pStalDefnPage;
	CStalInputPage*		m_pStalInputPage;
	CStalDebugPage*		m_pStalDebugPage;

	// Generated message map functions
protected:
	//{{AFX_MSG(CStalSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STALSHEET_H__F1213080_72EF_11D2_8B46_444553540000__INCLUDED_)
