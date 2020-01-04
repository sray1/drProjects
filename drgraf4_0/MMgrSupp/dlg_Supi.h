// Dlg_CurI.h : header file
//
#ifndef _DLG_SUPI_H
#define _DLG_SUPI_H


#include "Def_Type.h"
#include "Def_Supp.h"
#include "MSupRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_SupI dialog

class AFX_EXT_CLASS CDlg_SupI : public CDialog
{
// Construction
public:
	CDlg_SupI(CWnd* pWnd);	// message filtered to View
    BOOL Create ();

// Dialog Data
	//{{AFX_DATA(CDlg_SupI)
	enum { IDD = IDD_SUP_IN };
	BOOL	m_bRx;
	BOOL	m_bRy;
	BOOL	m_bRz;
	BOOL	m_bTx;
	BOOL	m_bTy;
	BOOL	m_bTz;
	CString	m_SupID;
	BOOL	m_bTxG;
	BOOL	m_bTyG;
	BOOL	m_bTzG;
	BOOL	m_bRxG;
	BOOL	m_bRyG;
	BOOL	m_bRzG;
	//}}AFX_DATA
    CWnd*		m_pWnd;
	SUPPPROC	m_SuppProc;
	pDOUBLE		m_dStif;
	/////////////////////////////////////////////////
	JOINTCOORD  m_jcType;		//	JC_DEFAULT,
								//	JC_X_FIXEDDIR,
								//	JC_X_TAN_CURVE,
								//	JC_I_TAN_PATCH,
								//	JC_Z_NOR_PATCH


protected:

//	void		GetJCType(); 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_SupI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_SupI)
	afx_msg void OnUpdate();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeSupid();
	virtual void OnCancel();
	afx_msg void OnSkewed();
	afx_msg void OnStiffness();
	afx_msg void OnSelchangeJctype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////
#endif
