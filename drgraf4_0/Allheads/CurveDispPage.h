#if !defined(AFX_CURVEDISPPAGE_H__AA812A6F_7244_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CURVEDISPPAGE_H__AA812A6F_7244_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CurveDispPage.h : header file
//

#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CCurveDispPage dialog

class CCurveDispPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCurveDispPage)

// Construction
public:
	CCurveDispPage();
	~CCurveDispPage();

// Dialog Data
	//{{AFX_DATA(CCurveDispPage)
	enum { IDD = IDD_CURVE_DISP };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCurveDispPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCurveDispPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVEDISPPAGE_H__AA812A6F_7244_11D2_8B46_444553540000__INCLUDED_)
