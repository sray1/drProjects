#if !defined(AFX_OBJ3DSHEET_H__F121307D_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_OBJ3DSHEET_H__F121307D_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Obj3DSheet.h : header file
//


#include "DrPropSheet.h"
#include "Obj3DInputPage.h"
#include "Obj3DGeomPage.h"
//#include "Obj3DDLoadPage.h"
//#include "Obj3DDDispPage.h"
//#include "Obj3DDSuppPage.h"
//#include "Obj3DDRestPage.h"
#include "Obj3DDebugPage.h"
/////////////////////////////////////////////////////////////////////////////
// CObj3DSheet

class CObj3DSheet : public CDrPropSheet
{
	DECLARE_DYNAMIC(CObj3DSheet)

// Construction
public:
	CObj3DSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CObj3DSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:
	virtual int	UpdateSheet(CString& strItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObj3DSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CObj3DSheet();

protected:
	CObj3DGeomPage*		m_pObj3DGeomPage;
	CObj3DInputPage*	m_pObj3DInputPage;
//	CObj3DLoadPage*		m_pObj3DLoadPage;
//	CObj3DDispPage*		m_pObj3DDispPage;
//	CObj3DRestPage*		m_pObj3DRestPage;
//	CObj3DSuppPage*		m_pObj3DSuppPage;
	CObj3DDebugPage*	m_pObj3DDebugPage;

	// Generated message map functions
protected:
	//{{AFX_MSG(CObj3DSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJ3DSHEET_H__F121307D_72EF_11D2_8B46_444553540000__INCLUDED_)
