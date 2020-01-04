// dlg_CooP.h : header file
//

#ifndef _DLG_SI_REVOLV_H
#define _DLG_SI_REVOLV_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MSolRsrc.h"
#include "DrPatch.h"
#include "SasePage.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_SI_Revolv dialog

class AFX_EXT_CLASS CDlg_SI_Revolv : public CSasePage
{
	DECLARE_DYNCREATE(CDlg_SI_Revolv)

// Construction
public:
	CDlg_SI_Revolv();   // standard constructor
	CDlg_SI_Revolv(CWnd* pParentWnd,SOLIDPROC SolProc); 
	~CDlg_SI_Revolv();
	virtual void ResetDlg();


protected:
	
	void FillListAllString_Node();
	void FillListAllString_Solid();
	void FillListAllString_Patch();


public:
// Dialog Data
	//{{AFX_DATA(CDlg_SI_Revolv)
	enum { IDD = IDD_SOL_IN_REVOLV };
	CString	m_Orient_P;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_SI_Revolv)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdate();
	afx_msg void OnSelchangePid();
	afx_msg void OnSelchangeSid();
	afx_msg void OnSelchangeNid();
	afx_msg void OnClosed();
	afx_msg void OnCancel();
	afx_msg void OnGenBCurve();
	afx_msg void OnGenBPatch();
	afx_msg void OnKillfocusCoord();
	afx_msg void OnAxisZ();
	afx_msg void OnAxisX();
	afx_msg void OnAxisY();
	afx_msg void OnAxis();
	afx_msg void OnNegative();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
