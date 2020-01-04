// dlg_CooP.h : header file
//

#ifndef _DLG_SI_GORDON_H
#define _DLG_SI_GORDON_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MSolRsrc.h"
#include "DrSolid.h"
#include "SasePage.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_SI_Gordon dialog

class AFX_EXT_CLASS CDlg_SI_Gordon : public CSasePage
{
	DECLARE_DYNCREATE(CDlg_SI_Gordon)

// Construction
public:
	CDlg_SI_Gordon();   // standard constructor
	CDlg_SI_Gordon(CWnd* pParentWnd,SOLIDPROC SolProc); 
	~CDlg_SI_Gordon();
	virtual void ResetDlg();

protected:
	
	void FillListAllString_Solid();
	void FillListAllString_Patch();


public:
// Dialog Data
	//{{AFX_DATA(CDlg_SI_Gordon)
	enum { IDD = IDD_SOL_IN_GORDON };
	CString	m_Orient_P;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_SI_Gordon)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdate();
	afx_msg void OnSelchangePid();
	afx_msg void OnSelchangeSid();
	afx_msg void OnCancel();
	afx_msg void OnAdvanced();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
