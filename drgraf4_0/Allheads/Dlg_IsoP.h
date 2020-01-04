// Dlg_IsoP.h : header file
//

#ifndef _DLG_ISOP_H
#define _DLG_ISOP_H


#include "Def_StaL.h"
#include "MStLRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_IsoP dialog

class AFX_EXT_CLASS CDlg_IsoP : public CDialog
{
// Construction
public:
	CDlg_IsoP(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg_IsoP)
	enum { IDD = IDD_ISOPAR };
	double	m_dStart;
	//}}AFX_DATA
	int			m_nCompo;
	STALPROC	m_StaLProc;
	CString		m_Heading;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_IsoP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_IsoP)
	afx_msg void OnOk();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////
#endif
