#if !defined(AFX_CURVETOPOPAGE_H__AA812A69_7244_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CURVETOPOPAGE_H__AA812A69_7244_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CurveTopoPage.h : header file
//

#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CCurveTopoPage dialog

class CCurveTopoPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCurveTopoPage)

// Construction
public:
	CCurveTopoPage();
	~CCurveTopoPage();

// Dialog Data
	//{{AFX_DATA(CCurveTopoPage)
	enum { IDD = IDD_CURVE_TOPO };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


	int		UpdateObjData(CString& strItemID);


protected:

	int		UpdateCombo(CDListMgr* pList, UINT DlgComboID);

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCurveTopoPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCurveTopoPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVETOPOPAGE_H__AA812A69_7244_11D2_8B46_444553540000__INCLUDED_)
