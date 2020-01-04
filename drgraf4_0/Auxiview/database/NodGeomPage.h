#if !defined(AFX_NODGEOMPAGE_H__FF628E78_5915_11D2_8A0E_00A0CC30503B__INCLUDED_)
#define AFX_NODGEOMPAGE_H__FF628E78_5915_11D2_8A0E_00A0CC30503B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NodGeomPage.h : header file
//

#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CNodGeomPage dialog

class CNodGeomPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CNodGeomPage)

// Construction
public:
	CNodGeomPage();
	~CNodGeomPage();

// Dialog Data
	enum { IDS = IDS_NODEGEOM };

	//{{AFX_DATA(CNodGeomPage)
	enum { IDD = IDD_NODEGEOM };
	CString	m_NGText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNodGeomPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNodGeomPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NODGEOMPAGE_H__FF628E78_5915_11D2_8A0E_00A0CC30503B__INCLUDED_)
