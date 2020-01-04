#if !defined(AFX_CUR_P_LOAD_H__F1213045_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CUR_P_LOAD_H__F1213045_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Cur_P_Load.h : header file
//

#include "DrStatic.h"
#include "Def_StaL.h"
#include "DrProf_C.h"
#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CCur_PLoadPage dialog

class CCur_PLoadPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCur_PLoadPage)

// Construction
public:
	CCur_PLoadPage();
	~CCur_PLoadPage();

// Dialog Data
	//{{AFX_DATA(CCur_PLoadPage)
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

	int		UpdateObjData(CString& strItemID);


protected:

	int		UpdateCombo(CDListMgr* pList, UINT DlgComboID);
	void	FillLinearStaticLoadInfo(CDrStatic* pStatic); 
	void	GetCreateBase(CString& strCreateBase,CDrStatic* pStatic); 
	void	FillLoadType(STALPROC  stalproc); 



protected:

	CDrProf_C*	m_pCurrentObject;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCur_PLoadPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCur_PLoadPage)
	afx_msg void OnSelchangeStalcombo();
	afx_msg void OnSelchangeSpelcombo();
	afx_msg void OnSelchangeDynlcombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUR_P_LOAD_H__F1213045_72EF_11D2_8B46_444553540000__INCLUDED_)
