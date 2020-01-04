#if !defined(AFX_SUPP_DEFN_H__F1213075_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_SUPP_DEFN_H__F1213075_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Supp_Defn.h : header file
//

#include "DrLinSup.h"
#include "Def_Supp.h"
#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CSuppDefnPage dialog

class CSuppDefnPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSuppDefnPage)

// Construction
public:
	CSuppDefnPage();
	~CSuppDefnPage();

// Dialog Data
	//{{AFX_DATA(CSuppDefnPage)
	enum { IDD = IDD_SUPP_DEFN };
	BOOL	m_bSkewed;
	CString	m_SuppType;
	double	m_TX;
	double	m_RX;
	double	m_TY;
	double	m_RY;
	double	m_TZ;
	double	m_RZ;
	CString	m_CreateBase;
	double	m_SKDirX;
	double	m_SKDirY;
	double	m_SKDirZ;
	BOOL	m_bTanORNor;
	CString	m_SuppID;
	//}}AFX_DATA

	int		UpdateObjData(CString& strItemID);


protected:

	int		UpdateCombo(CDListMgr* pList, UINT DlgComboID);
	void	FillLinearSupportInfo(CDrLinSup* pLinSup); 
	void	GetCreateBase(CString& strCreateBase,CDrLinSup* pSupp); 
	void	FillSuppType(SUPPPROC  suppproc); 



protected:

	CDrLinSup*	m_pCurrentObject;




// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSuppDefnPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSuppDefnPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPP_DEFN_H__F1213075_72EF_11D2_8B46_444553540000__INCLUDED_)
