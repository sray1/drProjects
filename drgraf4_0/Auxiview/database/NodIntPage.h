#if !defined(AFX_NODINTPAGE_H__FF628E79_5915_11D2_8A0E_00A0CC30503B__INCLUDED_)
#define AFX_NODINTPAGE_H__FF628E79_5915_11D2_8A0E_00A0CC30503B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NodIntPage.h : header file
//

#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CNodIntPage dialog

class CNodIntPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CNodIntPage)

// Construction
public:
	CNodIntPage();
	~CNodIntPage();

// Dialog Data
	enum { IDS = IDS_NODEINT };

	//{{AFX_DATA(CNodIntPage)
	enum { IDD = IDD_NODEINT };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNodIntPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNodIntPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NODINTPAGE_H__FF628E79_5915_11D2_8A0E_00A0CC30503B__INCLUDED_)
