#if !defined(AFX_SOLID_REST_H__F121306B_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_SOLID_REST_H__F121306B_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Solid_Rest.h : header file
//

#include "DBRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CSolidRestPage dialog

class CSolidRestPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSolidRestPage)

// Construction
public:
	CSolidRestPage();
	~CSolidRestPage();

// Dialog Data
	//{{AFX_DATA(CSolidRestPage)
	enum { IDD = IDD_SOLID_REST };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSolidRestPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSolidRestPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOLID_REST_H__F121306B_72EF_11D2_8B46_444553540000__INCLUDED_)
