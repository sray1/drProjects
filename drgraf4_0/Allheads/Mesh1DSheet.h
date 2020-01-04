#if !defined(AFX_MESH1DSHEET_H__F1213079_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_MESH1DSHEET_H__F1213079_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Mesh1DSheet.h : header file
//


#include "DrPropSheet.h"
#include "Mesh1DInputPage.h"
#include "Mesh1DGeomPage.h"
#include "Mesh1DLoadPage.h"
#include "Mesh1DSuppPage.h"
#include "Mesh1DRestPage.h"
#include "Mesh1DDebugPage.h"
/////////////////////////////////////////////////////////////////////////////
// CMesh1DSheet

class CMesh1DSheet : public CDrPropSheet
{
	DECLARE_DYNAMIC(CMesh1DSheet)

// Construction
public:
	CMesh1DSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMesh1DSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:
	virtual int	UpdateSheet(CString& strItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMesh1DSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMesh1DSheet();

protected:
	CMesh1DGeomPage*	m_pMesh1DGeomPage;
	CMesh1DInputPage*	m_pMesh1DInputPage;
	CMesh1DLoadPage*	m_pMesh1DLoadPage;
	CMesh1DRestPage*	m_pMesh1DRestPage;
	CMesh1DSuppPage*	m_pMesh1DSuppPage;
	CMesh1DDebugPage*	m_pMesh1DDebugPage;

	// Generated message map functions
protected:
	//{{AFX_MSG(CMesh1DSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESH1DSHEET_H__F1213079_72EF_11D2_8B46_444553540000__INCLUDED_)
