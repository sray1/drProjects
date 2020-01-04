#if !defined(AFX_CNodeRestPage_H__DD65B045_7096_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CNodeRestPage_H__DD65B045_7096_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CNodeRestPage.h : header file
//

#include "DrNode.h"
#include "DrFE0D.h"
#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CNodeRestPage dialog

class CNodeRestPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CNodeRestPage)

// Construction
public:
	CNodeRestPage();
	~CNodeRestPage();

// Dialog Data
	//{{AFX_DATA(CNodeRestPage)
	enum { IDD = IDD_NODE_REST };
	BOOL	m_bRelease;
	BOOL	m_bXR;
	BOOL	m_bX;
	BOOL	m_bY;
	BOOL	m_bYR;
	BOOL	m_bZ;
	BOOL	m_bZR;
	//}}AFX_DATA

	int		UpdateObjData(CString& strItemID,BOOL bCNode);
	int		UpdateMeshData(CString& strItemID,BOOL bCNode);
	int		UpdateInfo(CDrNode* pNode);



protected:

	CDrNode*	m_pCurrentNode;
	CDrFE0D*	m_pCurrentFE0D;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNodeRestPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNodeRestPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnRelease();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNodeRestPage_H__DD65B045_7096_11D2_8B46_444553540000__INCLUDED_)
