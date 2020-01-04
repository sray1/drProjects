#if !defined(AFX_OBJ3DGEOMPAGE_H__F1213085_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_OBJ3DGEOMPAGE_H__F1213085_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Obj3DGeomPage.h : header file
//

#include "DbRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CObj3DGeomPage dialog

class CObj3DGeomPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CObj3DGeomPage)

// Construction
public:
	CObj3DGeomPage();
	~CObj3DGeomPage();

// Dialog Data
	//{{AFX_DATA(CObj3DGeomPage)
	enum { IDD = IDD_OBJ3D_GEOM };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CObj3DGeomPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CObj3DGeomPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJ3DGEOMPAGE_H__F1213085_72EF_11D2_8B46_444553540000__INCLUDED_)
