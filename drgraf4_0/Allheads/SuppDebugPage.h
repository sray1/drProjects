#if !defined(AFX_SUPP_DEBUG_H__F1213076_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_SUPP_DEBUG_H__F1213076_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Supp_Debug.h : header file
//

#include "DBRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CSuppDebugPage dialog

class CSuppDebugPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSuppDebugPage)

// Construction
public:
	CSuppDebugPage();
	~CSuppDebugPage();

// Dialog Data
	//{{AFX_DATA(CSuppDebugPage)
	enum { IDD = IDD_SUPP_DEBUG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSuppDebugPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSuppDebugPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPP_DEBUG_H__F1213076_72EF_11D2_8B46_444553540000__INCLUDED_)
