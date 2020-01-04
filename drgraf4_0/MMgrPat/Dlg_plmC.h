// dlg_prlm.h : header file
//
#ifndef _DLG_PLMC_H
#define _DLG_PLMC_H

#include "MPatRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_pLMC dialog

class CDlg_pLMC : public CDialog
{
// Construction
public:
	CDlg_pLMC(CWnd* pParent = NULL);	// standard constructor

protected: 

	CBitmapButton	buttonOK,buttonCancel;

public:

// Dialog Data
	//{{AFX_DATA(CDlg_pLMC)
	enum { IDD = IDD_C_SPLICE_ROT };
	double	m_RotX;
	double	m_RotY;
	double	m_RotZ;
	CString	m_RotPtID;
	CString	m_FromID;
	CString	m_ToID;
	//}}AFX_DATA
	BOOL 	m_bCurve_Ist;	// not Used right now

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
			int  FillListAllString(UINT DlgItemID);
			void SetRotAngles();

	// Generated message map functions
	//{{AFX_MSG(CDlg_pLMC)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangeRotPt();
	afx_msg void OnEditchangeCnodeFrom();
	afx_msg void OnEditchangeCnodeTo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////////
#endif
