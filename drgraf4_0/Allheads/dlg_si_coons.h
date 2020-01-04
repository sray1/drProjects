// dlg_CooP.h : header file
//

#ifndef _DLG_SI_COONS_H
#define _DLG_SI_COONS_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MSolRsrc.h"
#include "DrSolid.h"
#include "SasePage.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_SI_Coons dialog

class AFX_EXT_CLASS CDlg_SI_Coons : public CSasePage
{
	DECLARE_DYNCREATE(CDlg_SI_Coons)

// Construction
public:
	CDlg_SI_Coons();   // standard constructor
	CDlg_SI_Coons(CWnd* pParentWnd,SOLIDPROC SolProc); 
	~CDlg_SI_Coons();
	virtual void ResetDlg();

protected:
	
	void FillListAllString_Solid();
	void FillListAllString_Patch();


public:
// Dialog Data
	//{{AFX_DATA(CDlg_SI_Coons)
	enum { IDD = IDD_SOL_IN_COONS };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_SI_Coons)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdate();
	afx_msg void OnSelchangePid();
	afx_msg void OnSelchangeSid();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
