#if !defined(AFX_CNodeLoadPage_H__DD65B044_7096_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CNodeLoadPage_H__DD65B044_7096_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CNodeLoadPage.h : header file
//

#include "DrStatic.h"
#include "Def_StaL.h"
#include "DrNode.h"
#include "DrFE0D.h"
#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CNodeLoadPage dialog

class CNodeLoadPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CNodeLoadPage)

// Construction
public:
	CNodeLoadPage();
	~CNodeLoadPage();

// Dialog Data
	//{{AFX_DATA(CNodeLoadPage)
	enum { IDD = IDD_NODE_LOAD };
	CString	m_LoadType;
	double	m_TX;
	double	m_RX;
	double	m_TY;
	double	m_RY;
	double	m_TZ;
	double	m_RZ;
	BOOL	m_bSkewed;
	CString	m_CreateBase;
	//}}AFX_DATA

	int		UpdateObjData(CString& strItemID,BOOL bCNode);
	int		UpdateMeshData(CString& strItemID,BOOL bCNode);


protected:

	int		UpdateCombo(CDListMgr* pList, UINT DlgComboID);
	void	FillLinearStaticLoadInfo(CDrStatic* pStatic); 
	void	GetCreateBase(CString& strCreateBase,CDrStatic* pStatic); 
	void	FillLoadType(STALPROC  stalproc); 



protected:

	CDrNode*	m_pCurrentNode;
	CDrFE0D*	m_pCurrentFE0D;



// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNodeLoadPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNodeLoadPage)
	afx_msg void OnSelchangeStalcombo();
	afx_msg void OnSelchangeSpelcombo();
	afx_msg void OnSelchangeDynlcombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNodeLoadPage_H__DD65B044_7096_11D2_8B46_444553540000__INCLUDED_)
