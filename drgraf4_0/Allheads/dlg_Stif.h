#ifndef _DLG_STIF_H
#define _DLG_STIF_H



#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SupStif.h : header file
//

#include "Def_Supp.h"
#include "MSupRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Stif dialog

class CDlg_Stif : public CDialog
{
// Construction
public:
	CDlg_Stif(CWnd* pParent = NULL);   // standard constructor


protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_Stif)
	enum { IDD = IDD_STIFFNESS };
	double	m_dFx;
	double	m_dFy;
	double	m_dFz;
	double	m_dMx;
	double	m_dMy;
	double	m_dMz;
	//}}AFX_DATA
	SUPPPROC	m_SuppProc;
	double		dValu[6];
	BOOL*		bKode;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_Stif)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_Stif)
	afx_msg void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
////////////////////////////////
#endif // _DLG_STIF_H
