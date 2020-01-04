#if !defined(AFX_MESH3DSHEET_H__F121307B_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_MESH3DSHEET_H__F121307B_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Mesh3DSheet.h : header file
//


#include "DrPropSheet.h"
#include "Mesh3DGeomPage.h"
#include "Mesh3DInputPage.h"
#include "Mesh3DLoadPage.h"
#include "Mesh3DSuppPage.h"
#include "Mesh3DRestPage.h"
#include "Mesh3DDebugPage.h"
/////////////////////////////////////////////////////////////////////////////
// CMesh3DSheet

class CMesh3DSheet : public CDrPropSheet
{
	DECLARE_DYNAMIC(CMesh3DSheet)

// Construction
public:
	CMesh3DSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMesh3DSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:
	virtual int	UpdateSheet(CString& strItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMesh3DSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMesh3DSheet();

protected:
	CMesh3DGeomPage*	m_pMesh3DGeomPage;
	CMesh3DInputPage*	m_pMesh3DInputPage;
	CMesh3DLoadPage*	m_pMesh3DLoadPage;
	CMesh3DRestPage*	m_pMesh3DRestPage;
	CMesh3DSuppPage*	m_pMesh3DSuppPage;
	CMesh3DDebugPage*	m_pMesh3DDebugPage;

	// Generated message map functions
protected:
	//{{AFX_MSG(CMesh3DSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESH3DSHEET_H__F121307B_72EF_11D2_8B46_444553540000__INCLUDED_)
