// Dlg_CurI.h : header file
//
#ifndef _DLGTHRI_H
#define _DLGTHRI_H


//#include "Glb_StaL.h"
#include "MStLRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_ThrI dialog

class AFX_EXT_CLASS CDlg_ThrI : public CDialog
{
// Construction
public:
	CDlg_ThrI(CWnd* pWnd);	// message filtered to View
    BOOL Create ();

// Dialog Data
	//{{AFX_DATA(CDlg_ThrI)
	enum { IDD = IDD_THERMAL_IN };
	double	m_dFx;
	CString	m_LoadID;
	//}}AFX_DATA
    CWnd*		m_pWnd;

protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_ThrI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_ThrI)
	afx_msg void OnUpdate();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeLoadid();
	afx_msg void OnAdvanced();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////
#endif
