#ifndef _DLG_LOFTCC_H
#define _DLG_LOFTCC_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Dlg_Tensor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_LoftCC dialog

class CDlg_LoftCC : public CDialog
{
// Construction
public:
	CDlg_LoftCC(CWnd* pParent = NULL);   // standard constructor

protected: 

	CBitmapButton	buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_LoftCC)
	enum { IDD = IDD_LOFTCC_PATCH };
	int		m_nCurve_U;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_LoftCC)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_LoftCC)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnChangeNodeU();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_TENSOR_H__C7BDC4C1_BF2A_11D2_8B46_444553540000__INCLUDED_)
