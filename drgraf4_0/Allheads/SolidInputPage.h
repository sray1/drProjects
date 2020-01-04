#if !defined(AFX_SOLID_INPUT_H__F121306D_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_SOLID_INPUT_H__F121306D_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Solid_Input.h : header file
//

#include "DBRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CSolidInputPage dialog

class CSolidInputPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSolidInputPage)

// Construction
public:
	CSolidInputPage();
	~CSolidInputPage();

// Dialog Data
	//{{AFX_DATA(CSolidInputPage)
	enum { IDD = IDD_SOLID_INPUT };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSolidInputPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSolidInputPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOLID_INPUT_H__F121306D_72EF_11D2_8B46_444553540000__INCLUDED_)
