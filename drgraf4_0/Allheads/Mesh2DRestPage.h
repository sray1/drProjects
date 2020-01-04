#if !defined(AFX_MESH2D_REST_H__F1213057_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_MESH2D_REST_H__F1213057_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Mesh2D_Rest.h : header file
//

#include "DBRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CMesh2DRestPage dialog

class CMesh2DRestPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMesh2DRestPage)

// Construction
public:
	CMesh2DRestPage();
	~CMesh2DRestPage();

// Dialog Data
	//{{AFX_DATA(CMesh2DRestPage)
	enum { IDD = IDD_MESH2D_REST };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMesh2DRestPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMesh2DRestPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESH2D_REST_H__F1213057_72EF_11D2_8B46_444553540000__INCLUDED_)
