// Dlg_CurI.h : header file
//
#ifndef _DLG_SUPA_H
#define _DLG_SUPA_H


#include "Def_Supp.h"
#include "MSupRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_SupA dialog

class AFX_EXT_CLASS CDlg_SupA : public CDialog
{
// Construction
public:
	CDlg_SupA(CWnd* pParent = NULL);	// standard constructor

protected:
	
	void	EnableControls(); 
	void	FillListAllNodeIDs_A();
	void	FillListAllNodeIDs_B();

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:

// Dialog Data
	//{{AFX_DATA(CDlg_SupA)
	enum { IDD = IDD_ADV_LSUP };
	BOOL	m_bRxG;
	BOOL	m_bRyG;
	BOOL	m_bRzG;
	BOOL	m_bTxG;
	BOOL	m_bTyG;
	BOOL	m_bTzG;
	CString	m_NID;
	BOOL	m_bTan;
	CString	m_NID_B;
	BOOL	m_bCN_a;
	BOOL	m_bCN_b;
	//}}AFX_DATA
    CWnd*		m_pWnd;
	BOOL		m_bRx;
	BOOL		m_bRy;
	BOOL		m_bRz;
	BOOL		m_bTx;
	BOOL		m_bTy;
	BOOL		m_bTz;
	BOOL		m_bPat;
	BOOL		m_bTanHide;
	BOOL		m_bIdBHide;

protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_SupA)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_SupA)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeNid();
	afx_msg void OnTangent();
	afx_msg void OnCnA();
	afx_msg void OnCnB();
	afx_msg void OnSelchangeNidb();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////
#endif

