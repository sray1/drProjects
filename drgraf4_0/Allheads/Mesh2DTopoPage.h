#if !defined(AFX_MESH2D_TOPO_H__F1213055_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_MESH2D_TOPO_H__F1213055_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Mesh2D_Topo.h : header file
//

#include "DBRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CMesh2DTopoPage dialog

class CMesh2DTopoPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMesh2DTopoPage)

// Construction
public:
	CMesh2DTopoPage();
	~CMesh2DTopoPage();

// Dialog Data
	//{{AFX_DATA(CMesh2DTopoPage)
	enum { IDD = IDD_MESH2D_TOPO };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMesh2DTopoPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMesh2DTopoPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESH2D_TOPO_H__F1213055_72EF_11D2_8B46_444553540000__INCLUDED_)
