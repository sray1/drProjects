#if !defined(AFX_PATCHSHEET_H__F1213077_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_PATCHSHEET_H__F1213077_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PatchSheet.h : header file
//


#include "DrPropSheet.h"
#include "PatchGeomPage.h"
#include "PatchInputPage.h"
#include "PatchLoadPage.h"
#include "PatchSuppPage.h"
#include "PatchRestPage.h"
#include "PatchDebugPage.h"
/////////////////////////////////////////////////////////////////////////////
// CPatchSheet

class CPatchSheet : public CDrPropSheet
{
	DECLARE_DYNAMIC(CPatchSheet)

// Construction
public:
	CPatchSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPatchSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:
	virtual int	UpdateSheet(CString& strItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPatchSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPatchSheet();

protected:
	CPatchGeomPage*		m_pPatchGeomPage;
	CPatchInputPage*	m_pPatchInputPage;
	CPatchLoadPage*		m_pPatchLoadPage;
	CPatchRestPage*		m_pPatchRestPage;
	CPatchSuppPage*		m_pPatchSuppPage;
	CPatchDebugPage*	m_pPatchDebugPage;

	// Generated message map functions
protected:
	//{{AFX_MSG(CPatchSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATCHSHEET_H__F1213077_72EF_11D2_8B46_444553540000__INCLUDED_)
