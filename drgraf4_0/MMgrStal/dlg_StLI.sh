// Dlg_CurI.h : header file
//
#ifndef _DLG_STLI_H
#define _DLG_STLI_H


//#include "Glb_StaL.h"
#include "MStLRsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_StLI dialog

class AFX_EXT_CLASS CDlg_StLI : public CDialog
{
// Construction
public:
	CDlg_StLI(CWnd* pWnd);	// message filtered to View
    BOOL Create ();

// Dialog Data
	//{{AFX_DATA(CDlg_StLI)
	enum { IDD = IDD_STATIC_IN };
	double	m_dFx;
	double	m_dFy;
	double	m_dFz;
	double	m_dMx;
	double	m_dMy;
	double	m_dMz;
	CString	m_LoadID;
	BOOL	m_bIsoPar;
	BOOL	m_bAdvanced;
	//}}AFX_DATA
    CWnd*		m_pWnd;
	CATEGORY	m_Category;
	/////////////////////// Dlg_StLA
	CString		m_NID;
	BOOL		m_bTan;
	CString		m_CID;
	BOOL		m_bIncrement;
	CString		m_Orient;
	double		m_dScale;
	double		m_dStep;
	double		m_dStart;
	

protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_StLI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_StLI)
	afx_msg void OnUpdate();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeLoadid();
	virtual void OnCancel();
	afx_msg void OnAdvanced();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////
#endif
