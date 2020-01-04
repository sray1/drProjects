#ifndef _CURGEOMPAGE_H
#define _CURGEOMPAGE_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CurGeomPage.h : header file
//

#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CCurGeomPage dialog

class CCurGeomPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCurGeomPage)

// Construction
public:
	CCurGeomPage();
	~CCurGeomPage();

// Dialog Data
	//{{AFX_DATA(CCurGeomPage)
	enum { IDD = IDD_CURGEOM };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCurGeomPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCurGeomPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif 

