#if !defined(AFX_MBJ3DSHEET_H__F121307C_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_MBJ3DSHEET_H__F121307C_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Mbj3DSheet.h : header file
//


#include "DrPropSheet.h"
#include "Mbj3DInputPage.h"
#include "Mbj3DGeomPage.h"
//#include "Mbj3DDLoadPage.h"
//#include "Mbj3DDDispPage.h"
//#include "Mbj3DDSuppPage.h"
//#include "Mbj3DDRestPage.h"
#include "Mbj3DDebugPage.h"
/////////////////////////////////////////////////////////////////////////////
// CMbj3DSheet

class CMbj3DSheet : public CDrPropSheet
{
	DECLARE_DYNAMIC(CMbj3DSheet)

// Construction
public:
	CMbj3DSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMbj3DSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:
	virtual int	UpdateSheet(CString& strItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMbj3DSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMbj3DSheet();

protected:
	CMbj3DGeomPage*		m_pMbj3DGeomPage;
	CMbj3DInputPage*	m_pMbj3DInputPage;
//	CMbj3DLoadPage*		m_pMbj3DLoadPage;
//	CMbj3DDispPage*		m_pMbj3DDispPage;
//	CMbj3DRestPage*		m_pMbj3DRestPage;
//	CMbj3DSuppPage*		m_pMbj3DSuppPage;
	CMbj3DDebugPage*	m_pMbj3DDebugPage;

	// Generated message map functions
protected:
	//{{AFX_MSG(CMbj3DSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MBJ3DSHEET_H__F121307C_72EF_11D2_8B46_444553540000__INCLUDED_)
