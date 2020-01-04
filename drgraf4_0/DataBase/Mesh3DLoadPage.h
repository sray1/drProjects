#if !defined(AFX_MESH3D_LOAD_H__F121305D_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_MESH3D_LOAD_H__F121305D_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Mesh3D_Load.h : header file
//

#include "DrStatic.h"
#include "Def_StaL.h"
#include "DrMesh3D.h"
#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CMesh3DLoadPage dialog

class CMesh3DLoadPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMesh3DLoadPage)

// Construction
public:
	CMesh3DLoadPage();
	~CMesh3DLoadPage();

// Dialog Data
	//{{AFX_DATA(CMesh3DLoadPage)
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

	CDrMesh3D*	m_pCurrentObject;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMesh3DLoadPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMesh3DLoadPage)
	afx_msg void OnSelchangeStalcombo();
	afx_msg void OnSelchangeSpelcombo();
	afx_msg void OnSelchangeDynlcombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESH3D_LOAD_H__F121305D_72EF_11D2_8B46_444553540000__INCLUDED_)
