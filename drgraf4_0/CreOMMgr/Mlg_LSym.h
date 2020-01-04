// Dlg_LMTR.h : header file
//
#ifndef _MLG_LSYM_H
#define _MLG_LSYM_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "CreMRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CMlg_LSym dialog

class AFX_EXT_CLASS CMlg_LSym : public CDialog
{
// Construction
public:
	CMlg_LSym(CWnd* pParent = NULL);   // standard constructor

protected: 

	CBitmapButton	buttonOK,buttonCancel;



public:

// Dialog Data
	//{{AFX_DATA(CMlg_LSym)
	enum { IDD = IDD_XFORM_SYMM };
	CString	m_FromID;
	CString	m_ToID;
	CString	m_RotPtID;
	//}}AFX_DATA
	CMatObj*	m_pMatObj;
	BOOL		m_bInstanced;



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMlg_LSym)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:

	void	SetUpLocalm(pMATRIX pM);
	void	GetUnitNormal(pWORLD pNormal); 


protected:

	int		FillListAllString(UINT DlgItemID,CString& IstID);



	// Generated message map functions
	//{{AFX_MSG(CMlg_LSym)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangeCnodeFrom();
	afx_msg void OnSelchangeCnodeTo();
	afx_msg void OnSelchangeRotpt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////
#endif
