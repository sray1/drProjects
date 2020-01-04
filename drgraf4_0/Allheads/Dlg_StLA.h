// Dlg_CurI.h : header file
//
#ifndef _DLG_STLA_H
#define _DLG_STLA_H


#include "Def_StaL.h"
#include "MStLRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_StLA dialog

class AFX_EXT_CLASS CDlg_StLA : public CDialog
{
// Construction
public:
	CDlg_StLA(CWnd* pParent = NULL);	// standard constructor

protected:
	
	void	EnableControls(); 
	void	FillListAllNodeIDs();

protected: 

	CBitmapButton buttonOK,buttonCancel;

public:

// Dialog Data
	//{{AFX_DATA(CDlg_StLA)
	enum { IDD = IDD_ADVANCE };
	CString	m_NID;
	BOOL	m_bTan;
	CString	m_NID_B;
	//}}AFX_DATA
    CWnd*		m_pWnd;
	BOOL		m_bPat;
	BOOL		m_bTanHide;
	BOOL		m_bIdBHide;


protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_StLA)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_StLA)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeNid();
	afx_msg void OnTangent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////
#endif
