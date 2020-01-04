#if !defined(AFX_CUR_PSHEET_H__F121307E_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CUR_PSHEET_H__F121307E_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Cur_PSheet.h : header file
//


#include "DrPropSheet.h"
#include "Cur_PGeomPage.h"
#include "Cur_PInputPage.h"
#include "Cur_PLoadPage.h"
#include "Cur_PSuppPage.h"
#include "Cur_PRestPage.h"
#include "Cur_PDebugPage.h"
#include <afxdlgs.h>

/////////////////////////////////////////////////////////////////////////////
// CCur_PSheet

class CCur_PSheet : public CDrPropSheet
{
	DECLARE_DYNAMIC(CCur_PSheet)

// Construction
public:
	CCur_PSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CCur_PSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:
	virtual int	UpdateSheet(CString& strItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCur_PSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCur_PSheet();

protected:
	CCur_PGeomPage*		m_pCur_PGeomPage;
	CCur_PInputPage*	m_pCur_PInputPage;
	CCur_PLoadPage*		m_pCur_PLoadPage;
	CCur_PRestPage*		m_pCur_PRestPage;
	CCur_PSuppPage*		m_pCur_PSuppPage;
	CCur_PDebugPage*	m_pCur_PDebugPage;

	// Generated message map functions
protected:
	//{{AFX_MSG(CCur_PSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUR_PSHEET_H__F121307E_72EF_11D2_8B46_444553540000__INCLUDED_)
