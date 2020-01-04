// Dlg_LMTR.h : header file
//
#ifndef _DLG_LMTR_H
#define _DLG_LMTR_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MCurRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_LMTR dialog

class CDlg_LMTR : public CDialog
{
// Construction
public:
	CDlg_LMTR(CWnd* pParent = NULL);   // standard constructor

protected: 

	CBitmapButton	buttonOK,buttonCancel;


public:

// Dialog Data
	//{{AFX_DATA(CDlg_LMTR)
	enum { IDD = IDD_LMAT_T_R };
	double	m_RotX;
	double	m_RotY;
	double	m_RotZ;
	double	m_TranX;
	double	m_TranY;
	double	m_TranZ;
	CString	m_RotPtID;
	CString	m_TranPtID;
	BOOL	m_bAngleIn;
	CString	m_FromID;
	CString	m_ToID;
	BOOL	m_bTangent;
	//}}AFX_DATA
	WORLD	m_Tangent;



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_LMTR)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	int		FillListAllString(UINT DlgItemID,CString& IstID);
	void	ShowTranslations(); 
	void	ShowRotations(); 


	// Generated message map functions
	//{{AFX_MSG(CDlg_LMTR)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangeTranPt();
	afx_msg void OnAngleInput();
	afx_msg void OnSelchangeCnodeFrom();
	afx_msg void OnSelchangeCnodeTo();
	afx_msg void OnTangent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////
#endif
