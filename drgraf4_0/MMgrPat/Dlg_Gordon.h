#ifndef _DLG_GORDON_H
#define _DLG_GORDON_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Dlg_Tensor.h : header file
//

#include "MPatRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Gordon dialog

class CDlg_Gordon : public CDialog
{
// Construction
public:
	CDlg_Gordon(CWnd* pParent = NULL);   // standard constructor

protected: 

	CBitmapButton	buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_Gordon)
	enum { IDD = IDD_GORDON_PATCH };
	int		m_nCurve_U;
	int		m_nCurve_V;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_Gordon)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_Gordon)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnChangeNodeV();
	afx_msg void OnChangeNodeU();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_TENSOR_H__C7BDC4C1_BF2A_11D2_8B46_444553540000__INCLUDED_)
