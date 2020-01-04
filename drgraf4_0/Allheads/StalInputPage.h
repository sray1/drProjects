#if !defined(AFX_STAL_INPUT_H__F1213071_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_STAL_INPUT_H__F1213071_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Stal_Input.h : header file
//

#include "DBRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CStalInputPage dialog

class CStalInputPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CStalInputPage)

// Construction
public:
	CStalInputPage();
	~CStalInputPage();

// Dialog Data
	//{{AFX_DATA(CStalInputPage)
	enum { IDD = IDD_STAL_INPUT };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CStalInputPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CStalInputPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAL_INPUT_H__F1213071_72EF_11D2_8B46_444553540000__INCLUDED_)
