// dlg_prlm.h : header file
//
#ifndef _DLG_PRLM_H
#define _DLG_PRLM_H

#include "MCurRsrc.h"
#include "MPatRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_PrLM dialog

class CDlg_PrLM : public CDialog
{
// Construction
public:
	CDlg_PrLM(CWnd* pParent = NULL);	// standard constructor

protected: 

	CBitmapButton	buttonOK,buttonCancel;

public:

// Dialog Data
	//{{AFX_DATA(CDlg_PrLM)
	enum { IDD = IDD_C_SPLICE_XFORM };
	double	m_RotX;
	double	m_RotY;
	double	m_RotZ;
	double	m_TranX;
	double	m_TranY;
	double	m_TranZ;
	CString	m_TranPtID;
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
	//{{AFX_MSG(CDlg_PrLM)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangeTranPt();
	afx_msg void OnSelchangeRotPt();
	afx_msg void OnEditchangeCnodeFrom();
	afx_msg void OnEditchangeCnodeTo();
	afx_msg void OnNoRot();
	afx_msg void OnNoTran();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////////
#endif
