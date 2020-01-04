#if !defined(AFX_MESH2D_DEBUG_H__F121304D_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_MESH2D_DEBUG_H__F121304D_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Mesh2D_Debug.h : header file
//

#include "DBRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CMesh2DDebugPage dialog

class CMesh2DDebugPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMesh2DDebugPage)

// Construction
public:
	CMesh2DDebugPage();
	~CMesh2DDebugPage();

// Dialog Data
	//{{AFX_DATA(CMesh2DDebugPage)
	enum { IDD = IDD_MESH2D_DEBUG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMesh2DDebugPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMesh2DDebugPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESH2D_DEBUG_H__F121304D_72EF_11D2_8B46_444553540000__INCLUDED_)
