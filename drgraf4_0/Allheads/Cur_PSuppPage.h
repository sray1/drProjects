#if !defined(AFX_CUR_P_SUPP_H__F1213043_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CUR_P_SUPP_H__F1213043_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Cur_P_Supp.h : header file
//

#include "DrLinSup.h"
#include "Def_Supp.h"
#include "DrProf_C.h"
#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CCur_PSuppPage dialog

class CCur_PSuppPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCur_PSuppPage)

// Construction
public:
	CCur_PSuppPage();
	~CCur_PSuppPage();

// Dialog Data
	//{{AFX_DATA(CCur_PSuppPage)
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

	CDrProf_C*	m_pCurrentObject;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCur_PSuppPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCur_PSuppPage)
	afx_msg void OnSelchangeSuppcombo();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUR_P_SUPP_H__F1213043_72EF_11D2_8B46_444553540000__INCLUDED_)
