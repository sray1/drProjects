// dlg_CooP.h : header file
//

#ifndef _DLG_PI_COONS_H
#define _DLG_PI_COONS_H


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "MPatRsrc.h"
#include "DrPatch.h"
#include "BasePage.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_PI_Coons dialog

class AFX_EXT_CLASS CDlg_PI_Coons : public CBasePage
{
	DECLARE_DYNCREATE(CDlg_PI_Coons)

// Construction
public:
	CDlg_PI_Coons();   // standard constructor
	CDlg_PI_Coons(CWnd* pParentWnd,PATCHPROC PatProc); 
	~CDlg_PI_Coons();
	virtual void ResetDlg();

protected:
	
	void FillListAllString_Curve();
	void FillListAllString_Patch();


public:
// Dialog Data
	//{{AFX_DATA(CDlg_PI_Coons)
	enum { IDD = IDD_PAT_IN_COONS };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CDlg_PI_Coons)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdate();
	afx_msg void OnSelchangePid();
	afx_msg void OnSelchangeCid();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
