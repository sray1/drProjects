// Dlg_CurI.h : header file
//
#ifndef _DLGPRSI_H
#define _DLGPRSI_H


//#include "Glb_StaL.h"
#include "MStLRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_PrsI dialog

class AFX_EXT_CLASS CDlg_PrsI : public CDialog
{
// Construction
public:
	CDlg_PrsI(CWnd* pWnd);	// message filtered to View
    BOOL Create ();

// Dialog Data
	//{{AFX_DATA(CDlg_PrsI)
	enum { IDD = IDD_PRESSURE_IN };
	double	m_dFx;
	CString	m_LoadID;
	//}}AFX_DATA
    CWnd*		m_pWnd;

protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_PrsI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_PrsI)
	afx_msg void OnUpdate();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeLoadid();
	afx_msg void OnAdvanced();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////
#endif
