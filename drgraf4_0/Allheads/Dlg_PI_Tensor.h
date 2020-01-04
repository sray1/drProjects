#if !defined(AFX_DLG_PI_TENSOR_H__C4D67361_C187_11D2_8B46_444553540000__INCLUDED_)
#define AFX_DLG_PI_TENSOR_H__C4D67361_C187_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Dlg_PI_Tensor.h : header file
//

#include "MPatRsrc.h"
#include "BasePage.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_PI_Tensor dialog
class AFX_EXT_CLASS CDlg_PI_Tensor : public CBasePage
{
	DECLARE_DYNCREATE(CDlg_PI_Tensor)

// Construction
public:
	CDlg_PI_Tensor();   // standard constructor
	CDlg_PI_Tensor(CWnd* pParentWnd,PATCHPROC PatProc);
	~CDlg_PI_Tensor();
	virtual void ResetDlg();

protected:
	
	void FillListAllString_Node();
	void FillListAllString_Patch();


public:
// Dialog Data
	//{{AFX_DATA(CDlg_PI_Tensor)
	enum { IDD = IDD_PAT_IN_TENSOR };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_PI_Tensor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_PI_Tensor)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdate();
	afx_msg void OnSelchangePid();
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
