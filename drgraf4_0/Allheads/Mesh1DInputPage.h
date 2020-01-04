#if !defined(AFX_MESH1DINPUTPAGE_H__F1213081_72EF_11D2_8B46_444553540000__INCLUDED_)
#define AFX_MESH1DINPUTPAGE_H__F1213081_72EF_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Mesh1DInputPage.h : header file
//

#include "DBRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CMesh1DInputPage dialog

class CMesh1DInputPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMesh1DInputPage)

// Construction
public:
	CMesh1DInputPage();
	~CMesh1DInputPage();

// Dialog Data
	//{{AFX_DATA(CMesh1DInputPage)
	enum { IDD = IDD_MESH1D_INPUT };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMesh1DInputPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMesh1DInputPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESH1DINPUTPAGE_H__F1213081_72EF_11D2_8B46_444553540000__INCLUDED_)
