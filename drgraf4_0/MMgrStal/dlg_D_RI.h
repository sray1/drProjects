// Dlg_CurI.h : header file
//
#ifndef _DLGD_RI_H
#define _DLGD_RI_H


//#include "Glb_StaL.h"
#include "MStLRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_D_RI dialog

class AFX_EXT_CLASS CDlg_D_RI : public CDialog
{
// Construction
public:
	CDlg_D_RI(CWnd* pWnd);	// message filtered to View
    BOOL Create ();

// Dialog Data
	//{{AFX_DATA(CDlg_D_RI)
	enum { IDD = IDD_DANDR_IN };
	double	m_dMx;
	double	m_dMy;
	double	m_dMz;
	double	m_dFx;
	double	m_dFy;
	double	m_dFz;
	CString	m_LoadID;
	//}}AFX_DATA
    CWnd*		m_pWnd;

protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_D_RI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_D_RI)
	afx_msg void OnUpdate();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeLoadid();
	afx_msg void OnAdvanced();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////
#endif
