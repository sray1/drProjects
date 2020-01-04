#if !defined(AFX_CURINTPAGE_H__FF628E76_5915_11D2_8A0E_00A0CC30503B__INCLUDED_)
#define AFX_CURINTPAGE_H__FF628E76_5915_11D2_8A0E_00A0CC30503B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CurIntPage.h : header file
//

#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CCurIntPage dialog

class CCurIntPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCurIntPage)

// Construction
public:
	CCurIntPage();
	~CCurIntPage();

// Dialog Data
	//{{AFX_DATA(CCurIntPage)
	enum { IDD = IDD_CURINT };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCurIntPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCurIntPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURINTPAGE_H__FF628E76_5915_11D2_8A0E_00A0CC30503B__INCLUDED_)
