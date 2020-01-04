// dlg_tang.h : header file
//
#ifndef _DLG_TANG_H
#define _DLG_TANG_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MCurRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Tang dialog

class AFX_EXT_CLASS CDlg_Tang : public CDialog
{
// Construction
public:
	CDlg_Tang(CWnd* pParent = NULL);	// standard constructor


protected: 

	CBitmapButton buttonOK,buttonCancel;


public:

// Dialog Data
	//{{AFX_DATA(CDlg_Tang)
	enum { IDD = IDD_BC_TAN };
	double	m_dTanX;
	double	m_dTanY;
	double	m_dTanZ;
	BOOL	m_bCoordIn;
	CString	m_FromID;
	CString	m_ToID;
	//}}AFX_DATA

// Implementation
protected:
	int		FillListAllString(UINT DlgItemID,CString& IstID);
	void	ShowTangent(); 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_LALL)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CDlg_Tang)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangeCnodeFrom();
	afx_msg void OnSelchangeCnodeTo();
	afx_msg void OnCoordInput();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
