// Dlg_CurI.h : header file
//
#ifndef _DLGLQCI_H
#define _DLGLQCI_H


#include "MCurRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_LQCI dialog

class AFX_EXT_CLASS CDlg_LQCI : public CDialog
{
// Construction
public:
	CDlg_LQCI(CWnd* pWnd);	// message filtered to View
    BOOL Create ();

// Dialog Data
	//{{AFX_DATA(CDlg_LQCI)
	enum { IDD = IDD_LQC_IN };
	CString	m_CID;
	CString	m_NID;
	int		m_nElperSeg;
	double	m_dRatio;
	BOOL	m_bAdvanceOn;
	BOOL	m_bClosed;
	double	m_dCoord;
	BOOL	m_bUniform;
	//}}AFX_DATA
    CWnd*	m_pWnd;


protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_LQCI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_LQCI)
	afx_msg void OnSelchangeCid();
	afx_msg void OnSelchangeNid();
	afx_msg void OnUpdate();
	virtual BOOL OnInitDialog();
	afx_msg void OnClosed();
	afx_msg void OnKillfocusCoord();
	afx_msg void OnCancel();
	afx_msg void OnUniform();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////
#endif
