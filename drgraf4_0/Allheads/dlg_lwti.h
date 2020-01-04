// Dlg_CurI.h : header file
//
#ifndef _DLGLWTI_H
#define _DLGLWTI_H


//#include "Glb_StaL.h"
#include "MStLRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_LWtI dialog

class AFX_EXT_CLASS CDlg_LWtI : public CDialog
{
// Construction
public:
	CDlg_LWtI(CWnd* pWnd);	// message filtered to View
    BOOL Create ();

// Dialog Data
	//{{AFX_DATA(CDlg_LWtI)
	enum { IDD = IDD_LUMPWT_IN };
	double	m_dFx;
	double	m_dFy;
	double	m_dFz;
	CString	m_LoadID;
	BOOL	m_bGravMul;
	//}}AFX_DATA
    CWnd*		m_pWnd;

protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_LWtI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_LWtI)
	afx_msg void OnUpdate();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeLoadid();
	afx_msg void OnAdvanced();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////
#endif
