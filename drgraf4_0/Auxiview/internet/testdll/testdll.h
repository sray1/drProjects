// testdll.h : main header file for the TESTDLL application
//

#if !defined(AFX_TESTDLL_H__A9539D0F_6284_11D2_8A0E_00A0CC30503B__INCLUDED_)
#define AFX_TESTDLL_H__A9539D0F_6284_11D2_8A0E_00A0CC30503B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestdllApp:
// See testdll.cpp for the implementation of this class
//

class CTestdllApp : public CWinApp
{
public:
	CTestdllApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestdllApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestdllApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLL_H__A9539D0F_6284_11D2_8A0E_00A0CC30503B__INCLUDED_)
