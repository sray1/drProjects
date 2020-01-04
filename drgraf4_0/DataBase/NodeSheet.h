#ifndef _NODESHEET_H
#define _NODESHEET_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CurSheet.h : header file
//


#include "DrPropSheet.h"
#include "NodeGeomPage.h"
#include "NodeInputPage.h"
#include "NodeLoadPage.h"
#include "NodeSuppPage.h"
#include "NodeRestPage.h"
#include "NodeDebugPage.h"
#include <afxdlgs.h>

/////////////////////////////////////////////////////////////////////////////
// CNodeSheet

class CNodeSheet : public CDrPropSheet
{
	DECLARE_DYNAMIC(CNodeSheet)

// Construction
public:
	CNodeSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CNodeSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CNodeSheet();

// Attributes
public:

// Operations
public:
	virtual int	UpdateSheet(CString& strItem);
	CString&	GetstrItem(){return m_strItem;};
	BOOL		IsCNode(){return m_bCNode;};
	BOOL		IsMNode(){return m_bMNode;};
	void		SetstrItem(CString& s){m_strItem = s;};
	void		SetCNode(BOOL b){m_bCNode = b;};
	void		SetMNode(BOOL b){m_bMNode = b;};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNodeSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNodeSheet();

protected:
	CNodeGeomPage*	m_pNodeGeomPage;
	CNodeInputPage* m_pNodeInputPage;
	CNodeLoadPage*	m_pNodeLoadPage;
	CNodeRestPage*	m_pNodeRestPage;
	CNodeSuppPage*	m_pNodeSuppPage;
	CNodeDebugPage* m_pNodeDebugPage;
	///////////////////
	CString			m_strItem;
	BOOL			m_bCNode;
	BOOL			m_bMNode;
	////////////////////////

	// Generated message map functions
protected:
	//{{AFX_MSG(CNodeSheet)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif   // _NODSHEET_H