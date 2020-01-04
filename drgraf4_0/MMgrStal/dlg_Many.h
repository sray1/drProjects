// Dlg_CurI.h : header file
//
#ifndef _DLG_MANY_H
#define _DLG_MANY_H


#include "Def_StaL.h"
#include "MStLRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_Many dialog

class AFX_EXT_CLASS CDlg_Many : public CDialog
{
// Construction
public:
	CDlg_Many(CWnd* pParent = NULL);   // standard constructor


protected: 

	CBitmapButton buttonOK,buttonCancel;

public:
// Dialog Data
	//{{AFX_DATA(CDlg_Many)
	enum { IDD = IDD_MANY_COMPO };
	double	m_dFx;
	double	m_dFy;
	double	m_dFz;
	double	m_dMx;
	double	m_dMy;
	double	m_dMz;
	//}}AFX_DATA
	STALPROC	m_StaLProc;
	double		dValu[6];
	BOOL*		bKode;
	CString		Nid;

protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_Many)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_Many)
	afx_msg void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////
#endif
