#if !defined(AFX_CURVERESTPAGE_H__AA812A6B_7244_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CURVERESTPAGE_H__AA812A6B_7244_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CurveRestPage.h : header file
//

#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CCurveRestPage dialog

class CCurveRestPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCurveRestPage)

// Construction
public:
	CCurveRestPage();
	~CCurveRestPage();

// Dialog Data
	//{{AFX_DATA(CCurveRestPage)
	enum { IDD = IDD_CURVE_REST };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCurveRestPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCurveRestPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVERESTPAGE_H__AA812A6B_7244_11D2_8B46_444553540000__INCLUDED_)
