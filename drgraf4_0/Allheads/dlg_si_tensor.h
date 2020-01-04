#if !defined(AFX_DLG_SI_TENSOR_H__C4D67361_C187_11D2_8B46_444553540000__INCLUDED_)
#define AFX_DLG_SI_TENSOR_H__C4D67361_C187_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Dlg_SI_Tensor.h : header file
//

#include "MSolRsrc.h"
#include "SasePage.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_SI_Tensor dialog
class AFX_EXT_CLASS CDlg_SI_Tensor : public CSasePage
{
	DECLARE_DYNCREATE(CDlg_SI_Tensor)

// Construction
public:
	CDlg_SI_Tensor();   // standard constructor
	CDlg_SI_Tensor(CWnd* pParentWnd,SOLIDPROC SolProc);
	~CDlg_SI_Tensor();
	virtual void ResetDlg();

protected:
	
	void FillListAllString_Node();
	void FillListAllString_Solid();


public:
// Dialog Data
	//{{AFX_DATA(CDlg_SI_Tensor)
	enum { IDD = IDD_SOL_IN_TENSOR };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_SI_Tensor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_SI_Tensor)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdate();
	afx_msg void OnSelchangeSid();
	afx_msg void OnSelchangeNid();
	afx_msg void OnClosed();
	afx_msg void OnAutoSeg();
	afx_msg void OnKillfocusSegAngle();
	afx_msg void OnCancel();
	afx_msg void OnAdvanced();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_PI_TENSOR_H__C4D67361_C187_11D2_8B46_444553540000__INCLUDED_)
/////////////////////////////////////////////////
