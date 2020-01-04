#if !defined(AFX_MESH2D_DISP_H__F121305A_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_MESH2D_DISP_H__F121305A_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Mesh2D_Disp.h : header file
//

#include "DBRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CMesh2DDispPage dialog

class CMesh2DDispPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMesh2DDispPage)

// Construction
public:
	CMesh2DDispPage();
	~CMesh2DDispPage();

// Dialog Data
	//{{AFX_DATA(CMesh2DDispPage)
	enum { IDD = IDD_MESH2D_DISP };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMesh2DDispPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMesh2DDispPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESH2D_DISP_H__F121305A_72EF_11D2_8B46_444553540000__INCLUDED_)
