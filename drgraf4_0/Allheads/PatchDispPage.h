#if !defined(AFX_PATCH_DISP_H__F1213067_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_PATCH_DISP_H__F1213067_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Patch_Disp.h : header file
//

#include "DBRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CPatchDispPage dialog

class CPatchDispPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPatchDispPage)

// Construction
public:
	CPatchDispPage();
	~CPatchDispPage();

// Dialog Data
	//{{AFX_DATA(CPatchDispPage)
	enum { IDD = IDD_PATCH_DISP };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPatchDispPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPatchDispPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATCH_DISP_H__F1213067_72EF_11D2_8B46_444553540000__INCLUDED_)
