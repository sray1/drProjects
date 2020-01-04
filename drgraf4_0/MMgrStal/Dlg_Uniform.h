#if !defined(AFX_DLG_UNIFORM_H__18103981_8E75_11D2_8B46_444553540000__INCLUDED_)
#define AFX_DLG_UNIFORM_H__18103981_8E75_11D2_8B46_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Dlg_Uniform.h : header file
//

#include "Def_StaL.h"
#include "MStLRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Uniform dialog

class CDlg_Uniform : public CDialog
{
// Construction
public:
	CDlg_Uniform(CWnd* pParent = NULL);   // standard constructor


protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_Uniform)
	enum { IDD = IDD_UNIFORM };
	double	m_dFx;
	double	m_dFy;
	double	m_dFz;
	double	m_dMx;
	double	m_dMy;
	double	m_dMz;
	//}}AFX_DATA
	STALPROC	m_StaLProc;
	double		m_dValu[6];
	BOOL*		m_bKode;
	UINT		m_GenKind;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_Uniform)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_Uniform)
	afx_msg void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_UNIFORM_H__18103981_8E75_11D2_8B46_444553540000__INCLUDED_)
