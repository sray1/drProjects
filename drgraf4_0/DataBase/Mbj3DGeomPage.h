#if !defined(AFX_MBJ3DGEOMPAGE_H__F1213088_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_MBJ3DGEOMPAGE_H__F1213088_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Mbj3DGeomPage.h : header file
//

#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CMbj3DGeomPage dialog

class CMbj3DGeomPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMbj3DGeomPage)

// Construction
public:
	CMbj3DGeomPage();
	~CMbj3DGeomPage();

// Dialog Data
	//{{AFX_DATA(CMbj3DGeomPage)
	enum { IDD = IDD_MBJ3D_GEOM };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMbj3DGeomPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMbj3DGeomPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MBJ3DGEOMPAGE_H__F1213088_72EF_11D2_8B46_444553540000__INCLUDED_)
