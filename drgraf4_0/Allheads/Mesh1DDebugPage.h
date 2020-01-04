#if !defined(AFX_MESH1D_DEBUG_H__F121304E_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_MESH1D_DEBUG_H__F121304E_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Mesh1D_Debug.h : header file
//

#include "DBRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CMesh1DDebugPage dialog

class CMesh1DDebugPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMesh1DDebugPage)

// Construction
public:
	CMesh1DDebugPage();
	~CMesh1DDebugPage();

// Dialog Data
	//{{AFX_DATA(CMesh1DDebugPage)
	enum { IDD = IDD_MESH1D_DEBUG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMesh1DDebugPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMesh1DDebugPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESH1D_DEBUG_H__F121304E_72EF_11D2_8B46_444553540000__INCLUDED_)
