#if !defined(AFX_STAL_DEBUG_H__F1213073_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_STAL_DEBUG_H__F1213073_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Stal_Debug.h : header file
//

#include "DBRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CStalDebugPage dialog

class CStalDebugPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CStalDebugPage)

// Construction
public:
	CStalDebugPage();
	~CStalDebugPage();

// Dialog Data
	//{{AFX_DATA(CStalDebugPage)
	enum { IDD = IDD_STAL_DEBUG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CStalDebugPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CStalDebugPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAL_DEBUG_H__F1213073_72EF_11D2_8B46_444553540000__INCLUDED_)
