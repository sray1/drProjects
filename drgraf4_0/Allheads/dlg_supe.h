// Dlg_CurI.h : header file
//
#ifndef _DLG_SUPE_H
#define _DLG_SUPE_H


#include "Def_Supp.h"
#include "DrLinSup.h"
#include "MSupRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_SupE dialog

class AFX_EXT_CLASS CDlg_SupE : public CDialog
{
// Construction
public:
	CDlg_SupE(CWnd* pParent = NULL);	// standard constructor
	CDlg_SupE( CDrLinSup* pDrLinSup,CWnd* pParent = NULL);	

protected:
	
	void	Init();
	void	UpdateSupInfo();
	void	EnableControls(); 
	void	FillListAllNodeIDs_A();
	void	FillListAllNodeIDs_B();

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:

// Dialog Data
	//{{AFX_DATA(CDlg_SupE)
	enum { IDD = IDD_SUP_EDIT };
	double	m_dFx;
	double	m_dFy;
	double	m_dFz;
	double	m_dMx;
	double	m_dMy;
	double	m_dMz;
	BOOL	m_bRx;
	BOOL	m_bRy;
	BOOL	m_bRz;
	BOOL	m_bTx;
	BOOL	m_bTy;
	BOOL	m_bTz;
	BOOL	m_bRxG;
	BOOL	m_bRyG;
	BOOL	m_bRzG;
	BOOL	m_bTxG;
	BOOL	m_bTyG;
	BOOL	m_bTzG;
	CString	m_aNid;
	CString	m_bNid;
	BOOL	m_bTan;
	CString	m_SupID;
	CString	m_strProc;
	BOOL	m_bCN_a;
	BOOL	m_bCN_b;
	//}}AFX_DATA
	BOOL		m_bSkewed;
	BOOL		m_bPat;
	BOOL		m_bTanCur;
	BOOL		m_bTanPat;
	BOOL		m_bNorPat;
	BOOL		m_bTanHide;
	BOOL		m_bIdBHide;
	SUPPPROC	m_SuppProc;
	UINT		m_SupBased;
	CDrLinSup*	m_pDrLinSup;	

protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_SupE)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_SupE)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeNid();
	afx_msg void OnTangent();
	afx_msg void OnCnB();
	afx_msg void OnCnA();
	afx_msg void OnSelchangeNidb2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////
#endif

