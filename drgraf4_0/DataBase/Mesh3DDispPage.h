#if !defined(AFX_MESH3D_DISP_H__F121305F_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_MESH3D_DISP_H__F121305F_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Mesh3D_Disp.h : header file
//

#include "DBRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CMesh3DDispPage dialog

class CMesh3DDispPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMesh3DDispPage)

// Construction
public:
	CMesh3DDispPage();
	~CMesh3DDispPage();

// Dialog Data
	//{{AFX_DATA(CMesh3DDispPage)
	enum { IDD = IDD_MESH3D_DISP };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMesh3DDispPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMesh3DDispPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESH3D_DISP_H__F121305F_72EF_11D2_8B46_444553540000__INCLUDED_)
