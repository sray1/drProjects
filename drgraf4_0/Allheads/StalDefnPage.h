#if !defined(AFX__STAL_DEFN_H__F1213072_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX__STAL_DEFN_H__F1213072_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// _Stal_Defn.h : header file
//

#include "DrStatic.h"
#include "Def_StaL.h"
#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CStalDefnPage dialog

class CStalDefnPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CStalDefnPage)

// Construction
public:
	CStalDefnPage();
	~CStalDefnPage();

// Dialog Data
	//{{AFX_DATA(CStalDefnPage)
	enum { IDD = IDD_STAL_DEFN };
	CString	m_StaLID;
	BOOL	m_bSkewed;
	CString	m_LoadType;
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
	//}}AFX_DATA

	int		UpdateObjData(CString& strItemID);


protected:

	int		UpdateCombo(CDListMgr* pList, UINT DlgComboID);
	void	FillLinearStaticLoadInfo(CDrStatic* pStatic); 
	void	GetCreateBase(CString& strCreateBase,CDrStatic* pStatic); 
	void	FillLoadType(STALPROC  stalproc); 



protected:

	CDrStatic*	m_pCurrentObject;




// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CStalDefnPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CStalDefnPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX__STAL_DEFN_H__F1213072_72EF_11D2_8B46_444553540000__INCLUDED_)
