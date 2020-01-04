// dlg_CooP.h : header file
//

#ifndef _DLG_SI_DUCT_H
#define _DLG_SI_DUCT_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MSolRsrc.h"
#include "DrSolid.h"
#include "SasePage.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_SI_Duct dialog

class AFX_EXT_CLASS CDlg_SI_Duct : public CSasePage
{
	DECLARE_DYNCREATE(CDlg_SI_Duct)

// Construction
public:
	CDlg_SI_Duct();   // standard constructor
	CDlg_SI_Duct(CWnd* pParentWnd,SOLIDPROC SolProc); 
	~CDlg_SI_Duct();
	virtual void ResetDlg();

protected:
	
	void FillListAllString_Node();
	void FillListAllString_Curve();
	void FillListAllString_Patch();
	void FillListAllString_Solid();


public:
// Dialog Data
	//{{AFX_DATA(CDlg_SI_Duct)
	enum { IDD = IDD_SOL_IN_DUCT };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_SI_Duct)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdate();
	afx_msg void OnSelchangeSid();
	afx_msg void OnSelchangePid();
	afx_msg void OnSelchangeCid();
	afx_msg void OnSelchangeNid();
	afx_msg void OnIncrement();
	afx_msg void OnCancel();
	afx_msg void OnDistrib();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
