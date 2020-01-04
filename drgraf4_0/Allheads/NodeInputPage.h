#if !defined(AFX_CNodeInputPage_H__DD65B041_7096_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CNodeInputPage_H__DD65B041_7096_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CNodeInputPage.h : header file
//

#include "DrNode.h"
#include "DrFE0D.h"
#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CNodeInputPage dialog

class CNodeInputPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CNodeInputPage)

// Construction
public:
	CNodeInputPage();
	~CNodeInputPage();

// Dialog Data
	//{{AFX_DATA(CNodeInputPage)
	enum { IDD = IDD_NODE_INPUT };
	BOOL	m_bCN_From;
	CString	m_FromID;
	BOOL	m_bCN_Ref;
	CString	m_RefID;
	BOOL	m_bCNTo;
	CString	m_ToID;
	double	m_X;
	double	m_Y;
	double	m_Z;
	double	m_Length;
	CString	m_ID;
	BOOL	m_bCN_MN;
	//}}AFX_DATA

	int		UpdateObjData(CString& strItemID,BOOL bCNode);
	int		UpdateMeshData(CString& strItemID,BOOL bCNode);
	int		UpdateInfo(CDrNode* pNode);



protected:

	CDrNode*	m_pCurrentNode;
	CDrFE0D*	m_pCurrentFE0D;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNodeInputPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNodeInputPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNodeInputPage_H__DD65B041_7096_11D2_8B46_444553540000__INCLUDED_)
