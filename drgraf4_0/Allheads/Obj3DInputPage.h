#if !defined(AFX_OBJ3DINPUTPAGE_H__F1213084_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_OBJ3DINPUTPAGE_H__F1213084_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Obj3DInputPage.h : header file
//

#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CObj3DInputPage dialog

class CObj3DInputPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CObj3DInputPage)

// Construction
public:
	CObj3DInputPage();
	~CObj3DInputPage();

// Dialog Data
	//{{AFX_DATA(CObj3DInputPage)
	enum { IDD = IDD_OBJ3D_INPUT };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CObj3DInputPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CObj3DInputPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJ3DINPUTPAGE_H__F1213084_72EF_11D2_8B46_444553540000__INCLUDED_)
