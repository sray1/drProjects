// Dlg_CurI.h : header file
//
#ifndef _DLGF_MI_H
#define _DLGF_MI_H


//#include "Glb_StaL.h"
#include "MStLRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_F_MI dialog

class AFX_EXT_CLASS CDlg_F_MI : public CDialog
{
// Construction
public:
	CDlg_F_MI(CWnd* pWnd);	// message filtered to View
    BOOL Create ();

// Dialog Data
	//{{AFX_DATA(CDlg_F_MI)
	enum { IDD = IDD_STATIC_IN };
	double	m_dMx;
	double	m_dMy;
	double	m_dMz;
	double	m_dFx;
	double	m_dFy;
	double	m_dFz;
	CString	m_LoadID;
	BOOL	m_bIsoPar;
	BOOL	m_bAdvanced;
	//}}AFX_DATA
    CWnd*		m_pWnd;
	CATEGORY	m_Category;
protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_F_MI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_F_MI)
	afx_msg void OnUpdate();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeLoadid();
	virtual void OnCancel();
	afx_msg void OnAdvanced();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////
#endif
