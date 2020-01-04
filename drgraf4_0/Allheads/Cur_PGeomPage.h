#if !defined(AFX_CUR_P_GEOM_H__F1213047_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CUR_P_GEOM_H__F1213047_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Cur_P_Geom.h : header file
//

#include "DListMgr.h"
#include "DBRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CCur_PGeomPage dialog

class CCur_PGeomPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCur_PGeomPage)

// Construction
public:
	CCur_PGeomPage();
	~CCur_PGeomPage();

// Dialog Data
	//{{AFX_DATA(CCur_PGeomPage)
	enum { IDD = IDD_CUR_P_GEOM };
	CString	m_Cur_P_ID;
	CString	m_Curve_ID;
	//}}AFX_DATA

	int		UpdateObjData(CString& strItemID);


protected:

	int		UpdateList(CDListMgr* pList, UINT DlgListID);


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCur_PGeomPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCur_PGeomPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUR_P_GEOM_H__F1213047_72EF_11D2_8B46_444553540000__INCLUDED_)
