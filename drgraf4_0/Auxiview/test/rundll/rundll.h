// rundll.h : main header file for the RUNDLL application
//

#if !defined(AFX_RUNDLL_H__B72ECA32_51F5_11D2_8A0E_00A0CC30503B__INCLUDED_)
#define AFX_RUNDLL_H__B72ECA32_51F5_11D2_8A0E_00A0CC30503B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRundllApp:
// See rundll.cpp for the implementation of this class
//

class CRundllApp : public CWinApp
{
public:
	CRundllApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRundllApp)
	public:
	virtual BOOL InitInstance();

	//}}AFX_VIRTUAL

// Implementation

	void InitDLLs();


	//{{AFX_MSG(CRundllApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUNDLL_H__B72ECA32_51F5_11D2_8A0E_00A0CC30503B__INCLUDED_)
