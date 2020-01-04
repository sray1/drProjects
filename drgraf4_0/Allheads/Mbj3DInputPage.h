#if !defined(AFX_MBJ3DINPUTPAGE_H__F1213087_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_MBJ3DINPUTPAGE_H__F1213087_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Mbj3DInputPage.h : header file
//

#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CMbj3DInputPage dialog

class CMbj3DInputPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMbj3DInputPage)

// Construction
public:
	CMbj3DInputPage();
	~CMbj3DInputPage();

// Dialog Data
	//{{AFX_DATA(CMbj3DInputPage)
	enum { IDD = IDD_MBJ3D_INPUT };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMbj3DInputPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMbj3DInputPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MBJ3DINPUTPAGE_H__F1213087_72EF_11D2_8B46_444553540000__INCLUDED_)
