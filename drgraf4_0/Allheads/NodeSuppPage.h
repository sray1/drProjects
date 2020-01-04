#if !defined(AFX_CNodeSuppPage_H__DD65B046_7096_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CNodeSuppPage_H__DD65B046_7096_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CNodeSuppPage.h : header file
//

#include "DrLinSup.h"
#include "Def_Supp.h"
#include "DrNode.h"
#include "DrFE0D.h"
#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CNodeSuppPage dialog

class CNodeSuppPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CNodeSuppPage)

// Construction
public:
	CNodeSuppPage();
	~CNodeSuppPage();

// Dialog Data
	//{{AFX_DATA(CNodeSuppPage)
	enum { IDD = IDD_NODE_SUPP };
	BOOL	m_bSkewed;
	CString	m_SuppType;
	double	m_TX;
	double	m_RX;
	double	m_TY;
	double	m_RY;
	double	m_TZ;
	double	m_RZ;
	CString	m_CreateBase;
	//}}AFX_DATA

	int		UpdateObjData(CString& strItemID,BOOL bCNode);
	int		UpdateMeshData(CString& strItemID,BOOL bCNode);


protected:

	int		UpdateCombo(CDListMgr* pList, UINT DlgComboID);
	void	FillLinearSupportInfo(CDrLinSup* pLinSup); 
	void	GetCreateBase(CString& strCreateBase,CDrLinSup* pSupp); 
	void	FillSuppType(SUPPPROC  suppproc); 



protected:

	CDrNode*	m_pCurrentNode;
	CDrFE0D*	m_pCurrentFE0D;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNodeSuppPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNodeSuppPage)
	afx_msg void OnSelchangeSuppcombo();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNodeSuppPage_H__DD65B046_7096_11D2_8B46_444553540000__INCLUDED_)
