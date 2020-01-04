// Dlg_LMTR.h : header file
//
#ifndef _DLG_LMR_H
#define _DLG_LMR_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MCurRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_LMR dialog

class CDlg_LMR : public CDialog
{
// Construction
public:
	CDlg_LMR(CWnd* pParent = NULL);   // standard constructor

protected: 

	CBitmapButton	buttonOK,buttonCancel;


public:

// Dialog Data
	//{{AFX_DATA(CDlg_LMR)
	enum { IDD = IDD_LMAT_R };
	double	m_RotX;
	double	m_RotY;
	double	m_RotZ;
	CString	m_RotPtID;
	BOOL	m_bAngleIn;
	CString	m_FromID;
	CString	m_ToID;
	BOOL	m_bTangent;
	//}}AFX_DATA
	WORLD	m_Tangent;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_LMR)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	int		FillListAllString(UINT DlgItemID,CString& IstID);
	void	ShowTranslations(); 
	void	ShowRotations(); 


	// Generated message map functions
	//{{AFX_MSG(CDlg_LMR)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnAngleInput();
	afx_msg void OnSelchangeCnodeFrom();
	afx_msg void OnSelchangeCnodeTo();
	afx_msg void OnTangent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////
#endif
