#if !defined(AFX_CUR_P_DEBUG_H__F1213041_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_CUR_P_DEBUG_H__F1213041_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Cur_P_Debug.h : header file
//

#include "DBRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CCur_PDebugPage dialog

class CCur_PDebugPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCur_PDebugPage)

// Construction
public:
	CCur_PDebugPage();
	~CCur_PDebugPage();

// Dialog Data
	//{{AFX_DATA(CCur_PDebugPage)
	enum { IDD = IDD_CUR_P_DEBUG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCur_PDebugPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCur_PDebugPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUR_P_DEBUG_H__F1213041_72EF_11D2_8B46_444553540000__INCLUDED_)
