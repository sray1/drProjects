#if !defined(AFX_SOLID_DISP_H__F121306F_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_SOLID_DISP_H__F121306F_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Solid_Disp.h : header file
//

#include "DBRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CSolidDispPage dialog

class CSolidDispPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSolidDispPage)

// Construction
public:
	CSolidDispPage();
	~CSolidDispPage();

// Dialog Data
	//{{AFX_DATA(CSolidDispPage)
	enum { IDD = IDD_SOLID_DISP };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSolidDispPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSolidDispPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOLID_DISP_H__F121306F_72EF_11D2_8B46_444553540000__INCLUDED_)
