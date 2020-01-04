#if !defined(AFX_CNodeGeomPage_H__DD65B047_7096_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CNodeGeomPage_H__DD65B047_7096_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CNodeGeomPage.h : header file
//

#include "DbRsrc.h"
#include "DrNode.h"
#include "DrFE0D.h"
/////////////////////////////////////////////////////////////////////////////
// CNodeGeomPage dialog

class CNodeGeomPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CNodeGeomPage)

// Construction
public:
	CNodeGeomPage();
	~CNodeGeomPage();

// Dialog Data
	//{{AFX_DATA(CNodeGeomPage)
	enum { IDD = IDD_NODE_GEOM };
	double	m_X;
	double	m_Y;
	double	m_Z;
	CString	m_ID;
	CString	m_strType;
	//}}AFX_DATA

	int		UpdateObjData(CString& strItemID,BOOL bCNode);
	int		UpdateMeshData(CString& strItemID,BOOL bCNode);
	int		UpdateInfo(CDrNode* pNode);



protected:

	CDrNode*	m_pCurrentNode;
	CDrFE0D*	m_pCurrentFE0D;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNodeGeomPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNodeGeomPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNodeGeomPage_H__DD65B047_7096_11D2_8B46_444553540000__INCLUDED_)
