#if !defined(AFX_MESH2DSHEET_H__F121307A_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_MESH2DSHEET_H__F121307A_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Mesh2DSheet.h : header file
//


#include "DrPropSheet.h"
#include "Mesh2DInputPage.h"
#include "Mesh2DGeomPage.h"
#include "Mesh2DLoadPage.h"
#include "Mesh2DSuppPage.h"
#include "Mesh2DRestPage.h"
#include "Mesh2DDebugPage.h"
/////////////////////////////////////////////////////////////////////////////
// CMesh2DSheet

class CMesh2DSheet : public CDrPropSheet
{
	DECLARE_DYNAMIC(CMesh2DSheet)

// Construction
public:
	CMesh2DSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMesh2DSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:
	virtual int	UpdateSheet(CString& strItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMesh2DSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMesh2DSheet();

protected:
	CMesh2DGeomPage*	m_pMesh2DGeomPage;
	CMesh2DInputPage*	m_pMesh2DInputPage;
	CMesh2DLoadPage*	m_pMesh2DLoadPage;
	CMesh2DRestPage*	m_pMesh2DRestPage;
	CMesh2DSuppPage*	m_pMesh2DSuppPage;
	CMesh2DDebugPage*	m_pMesh2DDebugPage;

	// Generated message map functions
protected:
	//{{AFX_MSG(CMesh2DSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESH2DSHEET_H__F121307A_72EF_11D2_8B46_444553540000__INCLUDED_)
