#if !defined(AFX_MESH1D_SUPP_H__F1213050_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_MESH1D_SUPP_H__F1213050_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Mesh1D_Supp.h : header file
//

#include "DrLinSup.h"
#include "Def_Supp.h"
#include "DrMesh1D.h"
#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CMesh1DSuppPage dialog

class CMesh1DSuppPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMesh1DSuppPage)

// Construction
public:
	CMesh1DSuppPage();
	~CMesh1DSuppPage();

// Dialog Data
	//{{AFX_DATA(CMesh1DSuppPage)
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

	int		UpdateObjData(CString& strItemID);


protected:

	int		UpdateCombo(CDListMgr* pList, UINT DlgComboID);
	void	FillLinearSupportInfo(CDrLinSup* pLinSup); 
	void	GetCreateBase(CString& strCreateBase,CDrLinSup* pSupp); 
	void	FillSuppType(SUPPPROC  suppproc); 



protected:

	CDrMesh1D*	m_pCurrentObject;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMesh1DSuppPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMesh1DSuppPage)
	afx_msg void OnSelchangeSuppcombo();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESH1D_SUPP_H__F1213050_72EF_11D2_8B46_444553540000__INCLUDED_)
